#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/wait.h>
#define MAX_LINE 100

static void FreeArgs(int _last, char **_args)
{
    for (; _last >= 0; _last--)
    {
        free(_args[_last]);
    }
    free(_args);
}

static char **CreateArgs(int _size)
{
    char **args;
    int i;

    if ((args = (char **)malloc(sizeof(char *) * _size)) == NULL)
    {
        return NULL;
    }

    for (i = 0; i < MAX_LINE / 2 + 1; i++)
    {
        if ((args[i] = (char *)malloc(sizeof(char) * MAX_LINE)) == NULL)
        {
            FreeArgs(i - 1, args);
        }
        args[i][0] = 0;
    }

    return args;
}

static int execute(char *_read)
{
    char **args;
    int id, status;
    char *token;
    int size = 2;
    printf("_read:%s\n", _read);
    args = CreateArgs(MAX_LINE / 2 + 1);
    if (!args)
    {
        return -1;
    }

    token = strtok(_read, " \n");
    strcpy(args[0], token);
    while (token != NULL)
    {
        token = strtok(NULL, " \n");
        if (token != NULL)
        {
            strcpy(args[size - 1], token);
            size++;
        }
    }

    args[size - 1] = NULL;
    id = fork();
    if (id < 0)
    {
        printf("fork error\n");
        exit(-1);
    }
    else if (id > 0)
    {
        waitpid(-1, &status, 0);
    }
    else if (id == 0)
    {

        execvp(args[0], args);
        printf("execvp error\n");
        exit(-1);
    }

    FreeArgs(MAX_LINE / 2, args);

    return 0;
}

int main()
{

    char *token;
    char line[MAX_LINE];
    int exit = 0;

    while (exit != 1)
    {

        printf("my-shell>$ ");
        fflush(stdout);
        fgets(line, MAX_LINE, stdin);

        for (token = strtok(line, "  \n \t"); token != NULL; token = strtok(NULL, " \n \t"))
        {
            printf("str:%s\n", token);
            if (!strcmp(token, "exit"))
            {
                exit = 1;
            }
            else
            {
                if (0 < execute(token)) /* fork(), execvp(), waitpid() in here */
                {
                    return -1;
                }
            }
        }
    }

    return 0;
}
