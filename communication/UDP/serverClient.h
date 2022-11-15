#ifndef ___SERVER_CLIENT_H__
#define ___SERVER_CLIENT_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/* ifconfig: inet 10.0.2.15  <=> comp ipv4 ip*/
#define SERVER_IPV4 "10.0.2.15"

/* ifconfig: inet6 2cbc:719e:23f5:71ef  <=> comp ipv4 ip*/
#define SERVER_IPV6 "2cbc:719e:23f5:71ef"

/* must be greater then 1024 and smaller them 65535 */
#define SERVER_PORT 5555

/* buffer length */
#define LEN 128

#endif /* ___SERVER_CLIENT_H__ */
