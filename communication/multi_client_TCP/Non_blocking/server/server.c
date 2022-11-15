/**********************************************************************************
                                include && define
**********************************************************************************/
#include <fcntl.h> /* fcntl F_GETFL F_SETFL O_NONBLOCK*/

#include "../include/serverClient.h"
#include "../../../advc/genDoubleList/genDoubleList.h"
#include "../../../advc/genDoubleList/list_itr.h"
#include "../../../advc/genDoubleList/list_functions.h"

#define MSG "Whatsapppppp!!"
#define BACK_LOG 1020
#define MAX_CLIENTS 1000

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
    int m_counter;
};

/**********************************************************************************
                     Declaration of static Auxiliary Functions
**********************************************************************************/
static int Init(Server *_server);
static int CreateSocket(Socket *_serverSocket);
static void NonBlockingSocket(int *_sock);
static int CheckNewClients(Server *_server);
static void CheckCurClients(Server *_serve);
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
    int status;
    if (!_server)
    {
        return NOT_INITIALIZED;
    }

    while (1)
    {
        status = CheckNewClients(_server);
        if (status != ERR_OK)
        {
            return RUN_SERV_FAIL;
        }

        CheckCurClients(_server);
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
        perror("ListCreate failed");
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

    NonBlockingSocket(&_serverSocket->m_listeningSocket);

    memset(&_serverSocket->m_socketAddress, 0, sizeof(_serverSocket->m_socketAddress));
    _serverSocket->m_socketAddress.sin_addr.s_addr = inet_addr(SERVER_IPV4);
    _serverSocket->m_socketAddress.sin_port = htons(SERVER_PORT);
    _serverSocket->m_socketAddress.sin_family = AF_INET;

    return ERR_OK;
}

static void NonBlockingSocket(int *_sock)
{
    int flags;

    if ((flags = fcntl(*_sock, F_GETFL)) < 0) /* Error */
    {
        perror("fcntl.F_GETFL");
        return;
    }

    if (fcntl(*_sock, F_SETFL, flags | O_NONBLOCK) < 0) /* Error */
    {
        perror("fcntl.F_SETFL");
        return;
    }
}

static int CheckNewClients(Server *_server)
{
    int *socketPtr = NULL;
    struct sockaddr_in clientSin;
    socklen_t len = sizeof(clientSin);
    int clientSock;

    clientSock = accept(_server->m_serverSocket.m_listeningSocket, (struct sockaddr *)&clientSin, &len);

    if (_server->m_counter >= MAX_CLIENTS)
    {
        close(clientSock);
        _server->m_counter--;
    }
    else
    {
        if (clientSock < 0)
        {
            if (errno != EAGAIN && errno != EWOULDBLOCK)
            {
                perror("accept failed");
                return ACCEPT_FAIL;
            }

            return ERR_OK;
        }

        NonBlockingSocket(&clientSock);

        socketPtr = malloc(sizeof(int));
        if (!socketPtr)
        {
            close(clientSock);
            return ALLOCATION_FAIL;
        }

        *socketPtr = clientSock;

        if (ListPushTail(_server->m_clientsList, (void *)socketPtr) != LIST_SUCCESS)
        {
            return LIST_PUSH_FAIL;
        }

        _server->m_counter++;
    }

    return ERR_OK;
}

static void CheckCurClients(Server *_server)
{
    int *currentClientSocket = NULL;
    ListItr itr = ListItrBegin(_server->m_clientsList);
    ListItr end = ListItrEnd(_server->m_clientsList);
    int dataRecvStatus;

    while (itr != end)
    {
        currentClientSocket = (int *)ListItrGet(itr);

        dataRecvStatus = DataRecv(*currentClientSocket);
        if (dataRecvStatus == RECV_FAIL)
        {
            ListItrRemove(itr);
            DestroySocket(currentClientSocket);
            _server->m_counter--;
        }
        else if (dataRecvStatus == ERR_OK)
        {
            if (DataSend(*currentClientSocket) == SEND_FAIL)
            {
                ListItrRemove(itr);
                DestroySocket(currentClientSocket);
                _server->m_counter--;
            }
        }

        itr = ListItrNext(itr);
    }
}

static int DataRecv(int _sock)
{
    int readBytes;
    char buffer[LEN];

    readBytes = recv(_sock, buffer, LEN, 0);
    if (readBytes < 0)
    {
        if (errno != EAGAIN && errno != EWOULDBLOCK)
        {
            return RECV_FAIL;
        }
        return SKIP_ITR;
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
    int sentBytes;

    printf("Server send to client: %s\n\n", MSG);

    sentBytes = send(_sock, MSG, strlen(MSG), 0);
    if (sentBytes < 0)
    {
        if (errno != EAGAIN && errno != EWOULDBLOCK)
        {
            return SEND_FAIL;
        }
    }

    return ERR_OK;
}

static void DestroySocket(void *_clientSocket)
{
    close(*((int *)_clientSocket));
    free(_clientSocket);
}
