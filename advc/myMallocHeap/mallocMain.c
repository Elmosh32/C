#include <stdio.h>
#include <stdlib.h>
#include "myMalloc.h"

int main()
{
    void *mallocPtr;
    int *MetaData;
    void *MyMalloc1;

    if ((mallocPtr = (void *)malloc(1000)) == NULL)
    {
        printf("malloc fail!");
    }

    MyMallocInit(mallocPtr, 1000);
    MetaData = mallocPtr;

    printf("\n-------MyMallocInit: 1000---------\n");
    printf("MetaData1: %d \n", *MetaData);
    printf("MetaData2: %d \n", *(MetaData + 1));
    printf("MetaData3: %d \n", *(MetaData + 2));

    if ((MyMalloc1 = MyMalloc(mallocPtr, 985)) == NULL)
    {
        printf("\n-------MyMalloc: 985---------\n");
        printf("NULL\n");
    }
}
