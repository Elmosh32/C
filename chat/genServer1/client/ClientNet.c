#include "../../../advc/genDoubleList/genDoubleList.h"
#include "../../../advc/genDoubleList/list_itr.h"
#include "../../../advc/genDoubleList/list_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include "../protocol/protocol.h"
#include "ClientNet.h"
#include "UI.h"

struct ClientNet
{
    int m_activeFlag;
    char m_userName[NAME_LEN_MAX + 1];
    char m_passWord[PASS_LEN_MAX + 1];
    int m_portServer;
    List *m_groups;
    char m_serverIP[17];
    int m_sock;
};

ClientNet *CreateClient(char *_serverIP, int _portServer)
{
    ClientNet *myClientNet;
    if ((myClientNet = (ClientNet *)malloc(sizeof(struct ClientNet))) == NULL)
    {
        return NULL;
    }
    myClientNet->m_activeFlag = 0;
    myClientNet->m_groups = ListCreate();
    if (myClientNet->m_groups == NULL)
    {
        free(myClientNet);
        return NULL;
    }
    strcpy(myClientNet->m_serverIP, _serverIP);
    myClientNet->m_portServer = _portServer;
    myClientNet->m_sock;
    return myClientNet;
}

int ConnectClient(ClientNet *_clientNet)
{
    struct sockaddr_in sin;
    int choise = 0;
    if (_clientNet == NULL)
    {
        return 0;
    }
    _clientNet->m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (_clientNet->m_sock < 0)
    {
        perror("socket failed");
        close(_clientNet->m_sock);
        return 0;
    }
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(_clientNet->m_serverIP);
    sin.sin_port = htons(_clientNet->m_portServer);
    if (connect(_clientNet->m_sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("connection failed");
        close(_clientNet->m_sock);
        _clientNet->m_sock = 0;
        return 0;
    }
    return 1;
}

int RecvFunc(ClientNet *_clientNet, char *_packet)
{
    int read_bytes;
    char tag;

    read_bytes = recv(_clientNet->m_sock, _packet, sizeof(_packet), 0);
    if (read_bytes <= 0)
    {
        perror("recv closed");
        close(_clientNet->m_sock);
        return -1;
    }
    else
    {
        return read_bytes;
    }
}

ProtocolErr SendFunc(ClientNet *_clientNet, char *_buffer)
{
    int sent_bytes;
    sent_bytes = send(_clientNet->m_sock, _buffer, strlen(_buffer), 0);

    if (sent_bytes <= 0)
    {
        perror("send failed");
        close(_clientNet->m_sock);
        return SENT_ERROR;
    }
    return SUCCESS;
}

void SetName(ClientNet *_clientNet, char *_name)
{
    strcpy(_clientNet->m_userName, _name);
}

void SetPassword(ClientNet *_clientNet, char *_pass)
{
    strcpy(_clientNet->m_passWord, _pass);
}