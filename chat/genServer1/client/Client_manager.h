#ifndef __CLIENT_MANAGER_H__
#define __CLIENT_MANAGER_H__
#include "../protocol/protocol.h"

typedef struct ClientManager ClientManager;

ClientManager *CreateClientManager(char *_serverIP, int _portServer);

ProtocolErr RunClientManager(ClientManager *_clientManager);

void DestroyClientManager(ClientManager **myClientMan);

#endif /*__CLIENT_MANAGER_H__*/
