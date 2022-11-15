#ifndef ___SERVER_CLIENT_H__
#define ___SERVER_CLIENT_H__

#include <sys/socket.h> /*  connect, send, socket, recv */
#include <netdb.h>
#include <errno.h>     /* errno EAI_AGAIN EWOULDBLOCK */
#include <unistd.h>    /* close */
#include <arpa/inet.h> /* inet_addr */
#include <string.h>    /* memset, strlen */
#include <stdio.h>     /* printf */
#include <stdlib.h>    /* rand */

/* ifconfig: inet = 10.0.2.15  <=>  ipv4 ip*/
#define SERVER_IPV4 "10.0.2.15"

/* ifconfig: inet6 = 2cbc:719e:23f5:71ef  <=>  ipv6 ip*/
#define SERVER_IPV6 "2cbc:719e:23f5:71ef"

/* must be greater than 1024 and smaller than 65535 */
#define SERVER_PORT 5555

/* buffer length */
#define LEN 4096

typedef enum Errors
{
    NOT_INITIALIZED,
    ALLOCATION_FAIL,
    LIST_PUSH_FAIL,
    RUN_SERV_FAIL,
    SKIP_ITR,
    ERR_OK = 0,
    SOCKET_FAIL = -1,
    REUSE_FAIL = -2,
    BIND_FAIL = -3,
    LISTEN_FAIL = -4,
    LIST_CREATE_FAIL = -5,
    ACCEPT_FAIL = -6,
    CONNECT_FAIL = -7,
    RECV_FAIL = -8,
    SEND_FAIL = -9,
    CLIENT_DISCONNECT = -10
} Errors;

typedef struct Server Server;

/**
 * @brief Creates a new Server
 * @param X
 * @return Server* - on success / NULL - on failure
 */
Server *CreateServer();

/**
 * @brief
 * @param _server: pointer to server
 * @return int - on success or on failure
 * @retval NOT_INITIALIZED if the Server pointer is not initialized
 * @retval ERR_OK on success
 */
int RunServer(Server *_server);

/**
 * @brief Destroys a given Server, NULLs the Server's pointer to prevent double destroy attempts
 * @param _server: Server to destroy
 * @return X
 */
void DestroyServer(Server **_server);

#endif /* ___SERVER_CLIENT_H__ */
