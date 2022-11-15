#include "serverClient.h"

#define MSG "Whatsapppppp serv"

static int ClientInit();
static int ClientConnect(struct sockaddr_in _clientSin, int _sock);
static int DataTransfer(int _sock);

int main()
{
    struct sockaddr_in sin;
    int sock, i;

    sock = ClientInit();
    if (sock == SOCKET_FAIL)
    {
        return 0;
    }

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(SERVER_IPV4);
    sin.sin_port = htons(SERVER_PORT);

    if (ClientConnect(sin, sock) == CONNECT_FAIL)
    {
        return 0;
    }

    for (i = 0; i < 5; i++)
    {
        if (DataTransfer(sock) != ERR_OK)
        {
            return 0;
        }
    }

    close(sock);
    return 0;
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

static int ClientConnect(struct sockaddr_in _clientSin, int _sock)
{

    if (connect(_sock, (struct sockaddr *)&_clientSin, sizeof(_clientSin)) < 0)
    {
        printf("connection failed");
        return CONNECT_FAIL;
    }

    return ERR_OK;
}

static int DataTransfer(int _sock)
{
    int read_bytes, sent_bytes;
    char buffer[LEN];

    printf("Client send to server: %s\n", MSG);

    sent_bytes = send(_sock, MSG, strlen(MSG), 0);
    if (sent_bytes < 0)
    {
        printf("Send Error\n");
        return SEND_FAIL;
    }

    read_bytes = recv(_sock, buffer, LEN, 0);
    if (read_bytes < 0)
    {
        printf("recv failed");
        return RECV_FAIL;
    }

    buffer[read_bytes] = '\0';
    printf("Server message : %s\n", buffer);

    return ERR_OK;
}