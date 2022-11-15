/**********************************************************************************
                                include && define
**********************************************************************************/
#include <time.h>
#include "../include/serverClient.h"

#define MSG "Whatsapppppp serv"
#define NUM_OF_CLIENTS 1000
#define THIRTY_PERCENT 30
#define FIVE_PERCENT 5
#define DISCONNECTED 0

/**********************************************************************************
                     Declaration of static Auxiliary Functions
**********************************************************************************/
static int ClientInit();
static int ClientConnect(struct sockaddr_in *_serverAddress);
static void ClientDisconnect(int _sock);
static int ServerData(int _sock);
static int DataRecv(int _sock);
static int DataSend(int _sock);

/**********************************************************************************
                                main Function
**********************************************************************************/
int main(void)
{
    int clientsArr[NUM_OF_CLIENTS] = {0};
    struct sockaddr_in serverAddress;
    size_t currentClient = 0;
    int percent, connectStat;

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(SERVER_IPV4);
    serverAddress.sin_port = htons(SERVER_PORT);

    while (1)
    {
        srand(time(NULL));
        percent = (rand() % 100) + 1;

        if (clientsArr[currentClient] == DISCONNECTED)
        {
            if (percent <= THIRTY_PERCENT)
            {
                connectStat = ClientConnect(&serverAddress);
                if (connectStat < 0)
                {
                    clientsArr[currentClient] = 0;
                    return 0;
                }
                else
                {
                    clientsArr[currentClient] = connectStat;
                }
            }
        }
        else
        {
            if (percent <= FIVE_PERCENT)
            {
                ClientDisconnect(clientsArr[currentClient]);
                clientsArr[currentClient] = 0;
            }
            else if (percent < THIRTY_PERCENT)
            {
                clientsArr[currentClient] = ServerData(clientsArr[currentClient]);
            }
        }

        currentClient = (currentClient + 1) % NUM_OF_CLIENTS;
    }

    return 0;
}

/**********************************************************************************
                        static Auxiliary Functions
**********************************************************************************/
static int ClientConnect(struct sockaddr_in *_serverAddress)
{
    int clientSocket;
    if ((clientSocket = ClientInit()) == SOCKET_FAIL)
    {
        return clientSocket;
    }

    if (connect(clientSocket, (struct sockaddr *)_serverAddress, sizeof(*_serverAddress)) < 0)
    {
        perror("connection failed");
        close(clientSocket);
        return -1;
    }

    return clientSocket;
}

static int ClientInit()
{
    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket failed");
        return SOCKET_FAIL;
    }

    return sock;
}

static int ServerData(int _sock)
{
    if (DataSend(_sock) == SEND_FAIL)
    {
        return 0;
    }
    else
    {
        if (DataRecv(_sock) != ERR_OK)
        {
            return 0;
        }
    }

    return _sock;
}

static int DataSend(int _sock)
{
    int sentBytes;
    char msg[100], str[100];
    sprintf(str, "client %d message: %s", _sock, MSG);
    strcpy(msg, str);

    printf("client %d send to server: %s\n", _sock, MSG);

    sentBytes = send(_sock, msg, strlen(msg), 0);
    if (sentBytes < 0)
    {
        printf("Send Error\n");
        return SEND_FAIL;
    }

    return ERR_OK;
}

static int DataRecv(int _sock)
{
    int readBytes;
    char buffer[LEN];

    readBytes = recv(_sock, buffer, LEN, 0);
    if (readBytes < 0)
    {
        printf("recv failed\n");
        return RECV_FAIL;
    }
    else if (readBytes == 0)
    {
        ClientDisconnect(_sock);
        return CLIENT_DISCONNECT;
    }

    buffer[readBytes] = '\0';
    printf("Server message : %s\n\n", buffer);

    return ERR_OK;
}

static void ClientDisconnect(int _sock)
{
    close(_sock);
}
