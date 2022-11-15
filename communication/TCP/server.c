#include "serverClient.h"

#define MSG "Whatsapppppp!!"
#define BACK_LOG 3

static int ServerInit(struct sockaddr_in _serverSin);
static int ServerConnect(struct sockaddr_in _clientSin, int _sock);
static int DataTransfer(int _sock);

int main()
{
    struct sockaddr_in serverSin;
    struct sockaddr_in clientSin;
    int sockInit, sockConnect, i;

    memset(&serverSin, 0, sizeof(serverSin));

    /*AF_INET=>ipv4, AF_INET6=ipv6 */
    serverSin.sin_family = AF_INET;
    serverSin.sin_addr.s_addr = inet_addr(SERVER_IPV4);
    serverSin.sin_port = htons(SERVER_PORT);

    sockInit = ServerInit(serverSin);
    if (sockInit == SOCKET_FAIL || sockInit == REUSE_FAIL || sockInit == BIND_FAIL || sockInit == LISTEN_FAIL)
    {
        return 0;
    }

    sockConnect = ServerConnect(clientSin, sockInit);
    if (sockConnect == ACCEPT_FAIL)
    {
        return 0;
    }

    for (i = 0; i < 7; i++)
    {
        if (DataTransfer(sockConnect) != ERR_OK)
        {
            return 0;
        }
    }

    close(sockConnect);

    return 0;
}

static int ServerInit(struct sockaddr_in _serverSin)
{
    int sock, optval = 1;

    /* SOCK_STREAM => tcp protocol */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket failed");
        return SOCKET_FAIL;
    }

    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        printf("reuse failed");
        return REUSE_FAIL;
    }

    if (bind(sock, (const struct sockaddr *)&_serverSin, sizeof(_serverSin)) < 0)
    {
        printf("bind failed");
        return BIND_FAIL;
    }

    if (listen(sock, BACK_LOG) < 0)
    {
        printf("listen failed");
        return LISTEN_FAIL;
    }

    return sock;
}

static int ServerConnect(struct sockaddr_in _clientSin, int _sock)
{
    int client_sock;
    int len = sizeof(_clientSin);

    client_sock = accept(_sock, (struct sockaddr *)&_clientSin, &len);
    if (client_sock < 0)
    {
        printf("accept failed");
        return ACCEPT_FAIL;
    }

    return client_sock;
}

static int DataTransfer(int _sock)
{
    int read_bytes, sent_bytes;
    char buffer[LEN];

    read_bytes = recv(_sock, buffer, sizeof(buffer), 0);
    if (read_bytes == 0)
    {
        printf("\nPEER CLOSED THE SOCKET!!\n");
        close(_sock);
        return PEER_CLOSED_THE_SOCKET;
    }
    else if (read_bytes < 0)
    {
        printf("recv failed");
        return RECV_FAIL;
    }

    buffer[read_bytes] = '\0';
    printf("Client message: %s\n", buffer);

    sent_bytes = send(_sock, MSG, strlen(MSG), 0);
    if (sent_bytes < 0)
    {
        printf("send failed\n");
        return SEND_FAIL;
    }
    printf("Server send to client: %s\n", MSG);

    return ERR_OK;
}