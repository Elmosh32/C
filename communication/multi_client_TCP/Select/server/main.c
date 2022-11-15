
#include "../include/serverClient.h"
#include <stdio.h>

int main(void)
{
    Server *server = CreateServer();
    if (server == NULL)
    {
        printf("CreateServer failed\n");
        return 1;
    }

    if ((RunServer(server)) != ERR_OK)
    {
        printf("RunServer failed\n");
        return 1;
    }

    DestroyServer(&server);

    return 0;
}