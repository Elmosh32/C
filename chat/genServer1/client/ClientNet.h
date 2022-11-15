#ifndef __CLIENTNET_H__
#define __CLIENTNET_H__
#include "../protocol/protocol.h"

typedef struct ClientNet ClientNet;
ClientNet *CreateClient(char *_serverIP, int _portServer);
int ConnectClient(ClientNet *_clientNet);
ProtocolErr SendFunc(ClientNet *_clientNet, char *_buffer);
int RecvFunc(ClientNet *_clientNet, char *_packet);
void SetName(ClientNet *_clientNet, char *_name);

void SetPassword(ClientNet *_clientNet, char *_pass);
#endif /*__CLIENTNET_H__*/
