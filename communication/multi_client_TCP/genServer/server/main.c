
#include "../include/serverClient.h"
#include <stdio.h>

/* ifconfig: inet = 10.0.2.15  <=>  ipv4 ip*/
#define SERVER_IPV4 "10.0.2.15"

/* ifconfig: inet6 = 2cbc:719e:23f5:71ef  <=>  ipv6 ip*/
#define SERVER_IPV6 "2cbc:719e:23f5:71ef"

/* must be greater than 1024 and smaller than 65535 */
#define SERVER_PORT 5555

/* buffer length */
#define LEN 4096
#define BACK_LOG 1020
#define MSG "HELLO"
#define CLIENT_ID 4

void NewClient(Client *_client)
{
    printf("new client:\nID=%d\nip=%s\nport=%d\n", _client->m_clientID, _client->m_clientIPAddress, _client->m_clientPort);
}

void CloseClient(int _clientID)
{
    printf("client %d closed\n\n", _clientID);
}

int ClientMessage(int _clientID, void *message)
{
    printf("Server send to client %d: %s\n\n", _clientID, (char *)message);

    return 0;
}

int ErrorsF(Errors _errorCode, void *_errorMsg)
{
    printf("error: %s\n\n", (char *)_errorMsg);
    return 0;
}

int main(void)
{
    Server *server = CreateServer(NewClient, CloseClient, ClientMessage, ErrorsF, SERVER_IPV4, SERVER_PORT, BACK_LOG);
    if (server == NULL)
    {
        printf("CreateServer failed\n");
        return 1;
    }

    if ((RunServer(server)) != ERR_OK)
    {
        printf("RunServer failed\n");
        return 1;
    }

    SendMsg(server, CLIENT_ID, (void *)MSG, strlen(MSG));
    DestroyServer(&server);

    return 0;
}