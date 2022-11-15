#include <stdio.h>
#include <unistd.h>
int g_var = 0;

int main()
{
    int l_var = 0;
    int n, i;
    n = fork();

    if (n > 0)
    {
        for (i = 0; i < 30; i++)
        {
            printf("father: l %d g %d\n", ++l_var, ++g_var);
            sleep(30);
        }
    }
    else
    {
        for (i = 0; i < 10; i++)
        {
            printf("son: l %d g %d\n", --l_var, --g_var);
            sleep(10);
        }
    }
    return 0;
}