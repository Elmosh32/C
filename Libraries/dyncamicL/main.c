#include <stdio.h>
#include "lib1.c"
#include "lib2.c"

/**
void printFile(char *name);
void printTime();
**/

int main()
{
    printFile(__FILE__);
    printTime();

    return 0;
}