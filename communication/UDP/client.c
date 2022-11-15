#include "serverClient.h"

#define MSG "Whatsapppppp serv"

int main()
{
    struct sockaddr_in6 sin;
    int sock, i;
    char buffer[LEN];
    int read_bytes, sent_bytes, len = sizeof(sin);

    sock = socket(AF_INET6, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror("socket failed");
        return 0;
    }

    memset(&sin, 0, sizeof(sin));
    sin.sin6_family = AF_INET;
    sin.sin6_port = htons(SERVER_PORT);
    inet_pton(AF_INET6, SERVER_IPV6, &sin.sin6_addr);

    for (i = 0; i < 5; i++)
    {
        sent_bytes = sendto(sock, MSG, strlen(MSG), 0, (const struct sockaddr *)&sin, sizeof(sin));
        if (sent_bytes < 0)
        {
            perror("sendto failed");
            return 0;
        }
        printf("Client send to server: Whatsapppppp serv\n");

        read_bytes = recvfrom(sock, buffer, LEN, 0, (struct sockaddr *)&sin, &len);
        if (read_bytes < 0)
        {
            perror("recvfrom failed");
            return 0;
        }
        buffer[read_bytes] = '\0';
        printf("Server message : %s\n", buffer);
    }
    close(sock);
    return 0;
}
