#include "serverNet.h"
#include "../protocol/protocol.h"
#include "userManager.h"
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>

#define PORT_NUM 1990
#define BACK_LOG 300
#define BUF_SEND 64
#define BUF_LEN 200

/* remove after test: */
typedef struct GroupManager
{
    int m_d;
} GroupManager;

typedef struct ServerManager
{
    Server *m_server;
    UserManager *m_userMng;
    GroupManager *m_groupMng;

} ServerManager;

void TreatRegistration(char *_userName, char *_password, void *_context, int _clientId)
{
    char bufferSend[BUF_SEND];
    char tag;
    int totalLen, status;
    status = AddToUsersMap(_userName, _password, ((ServerManager *)_context)->m_userMng);

    totalLen = PackRegAns(status, bufferSend);

    if (totalLen == 3)
    {
        SendMessage(((ServerManager *)_context)->m_server, _clientId, (void *)bufferSend, totalLen);
    }
}

void GotMessageFunc(char *_buf, int _readBytes, int _clientId, Server *_server, void *_context)
{
    int status;
    char tag;
    char messageBuf[BUF_LEN];
    char messageFail[BUF_SEND], userName[25], password[9];
    snprintf(messageFail, BUF_LEN, "Unvalid message from client %d", _clientId);

    /* status = UnPackMsg(_buf, _readBytes, messageBuf, &tag); */
    /*printf("%s \n", (char*)_buf);*/
    if (_buf == NULL || strlen(_buf) < 3)
    {
        SendMessage(_server, _clientId, (void *)messageFail, strlen(messageFail));
        return;
    }

    /* tag= atoi(_buf[0]); */
    tag = _buf[0];

    switch (tag)
    {
    case REG_REQUEST:
        UnPackRegRequest(_buf, _readBytes, userName, password); /* unpack puts values in username and password buffers*/
        TreatRegistration(userName, password, _context, _clientId);
        break;
    default:
        break;
    }
}

/*
void* TreatMessage( char* _buf, int _readBytes, int _clientId, Server* _server, void* _context )
{
    char bufferSend[BUF_SEND];
    snprintf(bufferSend, BUF_SEND,"Server: Hi client %d", _clientId);
    _buf[_readBytes]='\0';
    printf("%s \n", _buf);
    SendMessage(_server,_clientId,(void*)bufferSend, strlen(bufferSend) );
} */

ServerManager *CreateServerManager()
{
    ServerManager *mng = NULL;
    if ((mng = (ServerManager *)malloc(sizeof(ServerManager))) == NULL)
    {
        return NULL;
    }

    mng->m_userMng = UserManagerCreate();
    if (mng->m_userMng == NULL)
    {
        return NULL;
    }
    mng->m_groupMng = NULL; /* change when we add group manager*/
    mng->m_server = ServerCreate(NULL, GotMessageFunc, NULL, NULL, PORT_NUM, BACK_LOG, (void *)mng);
    if (mng->m_server == NULL)
    {
        return NULL;
    }
    return mng;
}

int main()
{
    ServerResult res;
    ServerManager *serverMng = CreateServerManager();

    if (serverMng == NULL)
    {
        printf("Failed creating the server\n");
    }
    else
    {
        res = RunServer(serverMng->m_server);
        if (res == FAILED_CONNECTION || res == FAILED_SELECT)
        {
            ServerDestroy(&serverMng->m_server);
/*             ReloadServer(NULL, GotMessageFunc, NULL, NULL, PORT_NUM, BACK_LOG);
 */        }
    }

    return 0;
}
