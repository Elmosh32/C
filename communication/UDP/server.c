#include "serverClient.h"

#define MSG "Whatsapppppp!!"

int main()
{
    struct sockaddr_in6 serverSin, clientSin;
    int sock, len, read_bytes, sent_bytes, i;
    char buffer[LEN];

    /* AF_INET=>ipv4, AF_INET6=ipv6 */
    /* SOCK_DGRAM => udp protocol */
    sock = socket(AF_INET6, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror("socket failed");
        return 0;
    }

    len = sizeof(clientSin);
    memset(&serverSin, 0, sizeof(serverSin));

    serverSin.sin6_family = AF_INET6;
    serverSin.sin6_port = htons(SERVER_PORT);
    inet_pton(AF_INET6, SERVER_IPV6, &serverSin.sin6_addr);

    /*     serverSin.sin6_addr = in6addr_any;*/

    if (bind(sock, (const struct sockaddr *)&serverSin, sizeof(serverSin)) < 0)
    {
        perror("bind failed");
        return 0;
    }

    for (i = 0; i < 5; i++)
    {
        read_bytes = recvfrom(sock, buffer, LEN, 0, (struct sockaddr *)&clientSin, (socklen_t *)&len);
        if (read_bytes < 0)
        {
            perror("recvfrom failed");
            return 0;
        }
        buffer[read_bytes] = '\0';
        printf("Client message: %s\n", buffer);

        sent_bytes = sendto(sock, MSG, strlen(MSG), 0, (const struct sockaddr *)&clientSin, len);
        if (sent_bytes < 0)
        {
            perror("sendto failed");
            return 0;
        }
        printf("Server send to client: Whatsapppppp!!\n");
    }

    close(sock);
    return 0;
}