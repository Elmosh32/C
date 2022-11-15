#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../protocol/protocol.h"
#include "ClientNet.h"
#include "UI.h"
#include "Client_manager.h"
#define NAME_LEN 24
#define PASS_LEN 8

struct ClientManager
{
    ClientNet *m_clientNet;
    int m_flagStop;
};

static int recvMsg(char *_msg, ClientManager *_myClientMan);
static int makeMsg(char *msg, ClientManager *myClientMan, char _tag);

ClientManager *CreateClientManager(char *_serverIP, int _portServer)
{
    ClientManager *myClientMan;
    if ((myClientMan = (ClientManager *)malloc(sizeof(struct ClientManager))) == NULL)
    {
        return NULL;
    }
    if ((myClientMan->m_clientNet = (ClientNet *)malloc(sizeof(ClientNet *))) == NULL)
    {
        free(myClientMan);
        return NULL;
    }
    if ((myClientMan->m_clientNet = CreateClient(_serverIP, _portServer)) == NULL)
    {
        free(myClientMan);
        return NULL;
    }
    myClientMan->m_flagStop = 0;
}

ProtocolErr RunClientManager(ClientManager *_clientManager)
{
    int choise = 0;
    ProtocolErr ressult;
    char tag;
    char *buffer;
    int status;
    if (!ConnectClient(_clientManager->m_clientNet))
    {
        return 0;
    }
    while (choise < 1 || choise > 3)
    {
        FirstMenu();
        scanf("%d", &choise);
        switch (choise)
        {
        case 1:
        {
            tag = REG_REQUEST;
            status = makeMsg(buffer, _clientManager, tag);
            recvMsg(buffer, _clientManager);
            break;
        }
        case 2:
        {
            /*             ressult = SendFunc(_clientManager->m_clientNet, LOGIN_REQUEST);
                        if (ressult != SUCCESS)
                        {
                            break;
                        }
                        ressult = RecvFunc(_clientManager->m_clientNet, &tag);
                        if (ressult != SUCCESS)
                        {
                            break;
                        } */
            break;
        }
        case 3:
        {
            CloseProg();
            break;
        }
        }
    }

    _clientManager->m_flagStop = 1;
    while (_clientManager->m_flagStop)
    {
        GroupMenu();
        return 1;
    }
}

void DestroyClientManager(ClientManager **myClientMan)
{
}

static int makeMsg(char *msg, ClientManager *myClientMan, char _tag)
{
    int sent_bytes;
    char buffer1[NAME_LEN], buffer2[PASS_LEN];
    char Packet[PACKET_SIZE];
    switch (_tag)
    {
    case REG_REQUEST:
    {
        EnterUserName();
        scanf("%s", buffer1);

        SetName(myClientMan->m_clientNet, buffer1);
        EnterPass();
        scanf("%s", buffer2);
        SetPassword(myClientMan->m_clientNet, buffer2);
        if ((PackRegRequest(buffer1, buffer2, Packet)) == INVALID_MSG)
        {
            return PACKING_ERROR;
        }
        SendFunc(myClientMan->m_clientNet, Packet);

        break;
    }
    case LOGIN_REQUEST:
    {
        EnterUserName();
        scanf("%s", buffer1);
        EnterPass();
        scanf("%s", buffer2);
        if ((PackRegRequest(buffer1, buffer2, Packet)) == INVALID_MSG)
        {
            return PACKING_ERROR;
        }
        break;
    }
    }
    return 1;
}

static int recvMsg(char *_msg, ClientManager *_myClientMan)
{
    char tag;
    char packet[PACKET_SIZE], buffer[PACKET_SIZE];
    int msgLen;
    msgLen = RecvFunc(_myClientMan->m_clientNet, packet);
    tag = getTag(packet);

    switch (tag)
    {
    case REG_REP:
    {
        if (UnPackRegAns(packet, buffer, msgLen) == INVALID_MSG)
        {
            return UNPACKING_ERROR;
        }
        if (buffer[0] == SUCCESS)
        {
            RegSuccess();
        }
        else
        {
            RegFail();
            return REG_ERROR;
        }
        break;
    }
    case LOGIN_OK:
    {
        LoginSuccess();
        break;
    }
    case LOGIN_FAILED:
    {
        /*             if (!UnPackRegAns(packet, read_bytes, buffer))
                    {
                        return UNPACKING_ERROR;
                    } */
        LoginFail();
        return LOGIN_ERROR;
    }
    }
    return 1;
}