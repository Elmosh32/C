#ifndef ___SERVER_CLIENT_H__
#define ___SERVER_CLIENT_H__

#include <sys/socket.h> /*  connect, send, socket, recv */
#include <netdb.h>
#include <string.h> /* memset, strlen */
#include <stdio.h>  /* printf */

/* ifconfig: inet = 10.0.2.15  <=>  ipv4 ip*/
#define SERVER_IPV4 "10.0.2.15"

/* ifconfig: inet6 = 2cbc:719e:23f5:71ef  <=>  ipv6 ip*/
#define SERVER_IPV6 "2cbc:719e:23f5:71ef"

/* must be greater than 1024 and smaller than 65535 */
#define SERVER_PORT 5555

/* buffer length */
#define LEN 128

typedef enum Errors
{
    ERR_OK = 10,
    PEER_CLOSED_THE_SOCKET = 0,
    SOCKET_FAIL = -1,
    REUSE_FAIL = -2,
    BIND_FAIL = -3,
    LISTEN_FAIL = -4,
    ACCEPT_FAIL = -5,
    CONNECT_FAIL = -6,
    RECV_FAIL = -7,
    SEND_FAIL = -8
} Errors;

#endif /* ___SERVER_CLIENT_H__ */
