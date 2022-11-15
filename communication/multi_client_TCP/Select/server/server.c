/**********************************************************************************
                                include && define
**********************************************************************************/
#include <fcntl.h> /* fcntl F_GETFL F_SETFL O_NONBLOCK*/
#include <sys/time.h>
#include <sys/select.h>
#include <signal.h>

#include "../include/serverClient.h"
#include "../../../../advc/genDoubleList/genDoubleList.h"
#include "../../../../advc/genDoubleList/list_itr.h"
#include "../../../../advc/genDoubleList/list_functions.h"

#define MSG "Whatsapppppp!!"
#define BACK_LOG 1020
#define MAX_CLIENTS 1000
#define MAX_FD 1024

/**********************************************************************************
                            Server & Socket structs
**********************************************************************************/
typedef struct Socket
{
    struct sockaddr_in m_socketAddress;
    int m_listeningSocket;
} Socket;

struct Server
{
    Socket m_serverSocket;
    List *m_clientsList;
    int m_numOfClients;
    fd_set m_master;
};

/**********************************************************************************
                     Declaration of static Auxiliary Functions
**********************************************************************************/
static int Init(Server *_server);
static int CreateSocket(Socket *_serverSocket);
static int CheckNewClients(Server *_server);
static void CheckCurClients(Server *_serve, fd_set _temp, int *_activity);
static int DataRecv(int _sock);
static int DataSend(int _sock);
static void DestroySocket(void *_clientSocket);

/**********************************************************************************
                                api Functions
**********************************************************************************/
Server *CreateServer()
{
    Server *server = malloc(sizeof(Server));
    if (!server)
    {
        return NULL;
    }

    if (Init(server) != ERR_OK)
    {
        if (server->m_clientsList)
        {
            ListDestroy(&server->m_clientsList, NULL);
        }

        free(server);
        return NULL;
    }

    return server;
}

int RunServer(Server *_server)
{
    int status, activity;
    fd_set readfds;

    if (!_server)
    {
        return NOT_INITIALIZED;
    }

    while (1)
    {
        FD_ZERO(&readfds);
        readfds = _server->m_master;
        activity = select(MAX_FD, &readfds, NULL, NULL, NULL);
        if (activity < 0 && errno != EINTR)
        {
            perror("select failed");
            return RUN_SERV_FAIL;
        }

        if (FD_ISSET(_server->m_serverSocket.m_listeningSocket, &readfds))
        {
            status = CheckNewClients(_server);
            if (status != ERR_OK && status != MAX_CLIENTS)
            {
                return RUN_SERV_FAIL;
            }
            if (status == ERR_OK)
            {
                activity--;
            }
        }

        if (activity)
        {
            CheckCurClients(_server, readfds, &activity);
        }
    }

    return ERR_OK;
}

void DestroyServer(Server **_server)
{
    if (_server && *_server)
    {
        ListDestroy(&(*_server)->m_clientsList, &DestroySocket);
        close((&((*_server)->m_serverSocket))->m_listeningSocket);
        free((*_server));
        (*_server) = NULL;
    }
}

/**********************************************************************************
                        static Auxiliary Functions
**********************************************************************************/
static int Init(Server *_server)
{
    int optval = 1;

    if ((CreateSocket(&_server->m_serverSocket)) == SOCKET_FAIL)
    {
        return SOCKET_FAIL;
    }

    _server->m_clientsList = ListCreate();
    if (!_server->m_clientsList)
    {
        printf("ListCreate failed");
        return LIST_CREATE_FAIL;
    }

    if (setsockopt(_server->m_serverSocket.m_listeningSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        perror("reuse failed");
        return REUSE_FAIL;
    }

    if (bind(_server->m_serverSocket.m_listeningSocket, (struct sockaddr *)&_server->m_serverSocket.m_socketAddress, sizeof(_server->m_serverSocket.m_socketAddress)) < 0)
    {
        perror("bind failed");
        return BIND_FAIL;
    }

    if (listen(_server->m_serverSocket.m_listeningSocket, BACK_LOG) < 0)
    {
        perror("listen failed");
        return LISTEN_FAIL;
    }

    FD_ZERO(&_server->m_master);
    FD_SET(_server->m_serverSocket.m_listeningSocket, &_server->m_master);

    return ERR_OK;
}

static int CreateSocket(Socket *_serverSocket)
{
    _serverSocket->m_listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket->m_listeningSocket < 0)
    {
        perror("socket failed");
        return SOCKET_FAIL;
    }

    memset(&_serverSocket->m_socketAddress, 0, sizeof(_serverSocket->m_socketAddress));
    _serverSocket->m_socketAddress.sin_addr.s_addr = inet_addr(SERVER_IPV4);
    _serverSocket->m_socketAddress.sin_port = htons(SERVER_PORT);
    _serverSocket->m_socketAddress.sin_family = AF_INET;

    return ERR_OK;
}

static int CheckNewClients(Server *_server)
{
    int *socketPtr = NULL;
    struct sockaddr_in clientSin;
    int clientSock;
    socklen_t len = sizeof(clientSin);

    clientSock = accept(_server->m_serverSocket.m_listeningSocket, (struct sockaddr *)&clientSin, &len);

    if (_server->m_numOfClients >= MAX_CLIENTS)
    {
        close(clientSock);
        _server->m_numOfClients--;
        return MAX_CLIENTS;
    }
    else
    {
        if (clientSock < 0)
        {
            perror("accept failed");
            return ACCEPT_FAIL;
        }

        socketPtr = malloc(sizeof(int));
        if (!socketPtr)
        {
            close(clientSock);
            return ALLOCATION_FAIL;
        }

        *socketPtr = clientSock;

        if (ListPushTail(_server->m_clientsList, (void *)socketPtr) != LIST_SUCCESS)
        {
            close(clientSock);
            free(socketPtr);
            return LIST_PUSH_FAIL;
        }

        _server->m_numOfClients++;
    }
    FD_SET(clientSock, &_server->m_master);
    return ERR_OK;
}

static void CheckCurClients(Server *_server, fd_set _temp, int *_activity)
{
    ListItr itr = ListItrBegin(_server->m_clientsList);
    ListItr end = ListItrEnd(_server->m_clientsList);
    int *currentClientSocket = NULL;
    int dataRecvStatus;
    while (!ListItrEquals(itr, end))
    {
        currentClientSocket = (int *)ListItrGet(itr);
        itr = ListItrNext(itr);
        if (FD_ISSET(*currentClientSocket, &_temp))
        {
            dataRecvStatus = DataRecv(*currentClientSocket);
            if (dataRecvStatus == RECV_FAIL || dataRecvStatus == CLIENT_DISCONNECT)
            {
                ListItrRemove(ListItrPrev(itr));
                FD_CLR(*currentClientSocket, &_server->m_master);
                DestroySocket(currentClientSocket);
                _server->m_numOfClients--;
            }
            else if (dataRecvStatus == ERR_OK)
            {
                if (DataSend(*currentClientSocket) == SEND_FAIL)
                {
                    ListItrRemove(ListItrPrev(itr));
                    FD_CLR(*currentClientSocket, &_server->m_master);
                    DestroySocket(currentClientSocket);
                    _server->m_numOfClients--;
                }
            }

            (*_activity)--;
            if (!(*_activity))
            {
                break;
            }
        }
    }
}

static int DataRecv(int _sock)
{
    int readBytes;
    char buffer[LEN];

    readBytes = recv(_sock, buffer, LEN, 0);
    if (readBytes < 0)
    {
        return RECV_FAIL;
    }
    else if (readBytes == 0)
    {
        return CLIENT_DISCONNECT;
    }

    buffer[readBytes] = '\0';
    printf("%s\n", buffer);

    return ERR_OK;
}

static int DataSend(int _sock)
{
    int sentBytes, i;

    printf("Server send to client: %s\n\n", MSG);

    sentBytes = send(_sock, MSG, strlen(MSG), 0);
    if (sentBytes < 0)
    {
        return SEND_FAIL;
    }
    else if (sentBytes != strlen(MSG))
    {
        return SEND_FAIL;
    }

    return ERR_OK;
}

static void DestroySocket(void *_clientSocket)
{
    close(*((int *)_clientSocket));
    free(_clientSocket);
}
