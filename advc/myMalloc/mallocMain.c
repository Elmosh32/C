#include <stdio.h>
#include <stdlib.h>
#include "myMalloc.h"

#define METADATA_AT_INDEX(memory, index) (((long *)memory)[index])

static void MyMallocInitT1();
static void MyMallocInitT2();
static void MyMallocInitT3();

static void MyMallocT1();
static void MyMallocT2();
static void MyMallocT3();
static void MyMallocT4();
static void MyMallocT5();
static void MyMallocT6();
static void MyMallocT7();

static void MyFreeT1();
static void MyFreeT2();
static void MyFreeT3();
static void MyFreeT4();

int main()
{
    printf("\n*************************************************************\n"
           "                     MyMallocInit tests\n"
           "*************************************************************\n");
    MyMallocInitT1();
    MyMallocInitT2();
    MyMallocInitT3();

    printf("\n*************************************************************\n"
           "                     MyMalloc tests\n"
           "*************************************************************\n");
    MyMallocT1();
    MyMallocT2();
    MyMallocT3();
    MyMallocT4();
    MyMallocT5();
    MyMallocT6();
    MyMallocT7();

    printf("\n*************************************************************\n"
           "                     MyFree tests\n"
           "*************************************************************\n");
    MyFreeT1();
    MyFreeT2();
    MyFreeT3();
    MyFreeT4();
    return 0;
}

static void MyMallocInitT1()
{
    MyMallocInit(NULL, 10000);

    printf("1)MyMallocInit\t=>\tPASS\n");
}

static void MyMallocInitT2()
{
    void *mallocPtr;

    if ((mallocPtr = (void *)malloc(10000)) == NULL)
    {
        printf("2)MyMallocInit\t=>\tmalloc fail\n");
        return;
    }

    MyMallocInit(mallocPtr, 24);

    if (METADATA_AT_INDEX(mallocPtr, 0) != 0)
    {
        printf("2)MyMallocInit\t=>\tFAIL\n");
        free(mallocPtr);
        return;
    }

    free(mallocPtr);
    printf("2)MyMallocInit\t=>\tPASS\n");
}

static void MyMallocInitT3()
{
    void *mallocPtr;

    if ((mallocPtr = (void *)malloc(10000)) == NULL)
    {
        printf("3)MyMallocInit\t=>\tmalloc fail\n");
        return;
    }

    MyMallocInit(mallocPtr, 28);

    if (METADATA_AT_INDEX(mallocPtr, 0) != 28)
    {
        printf("3)MyMallocInit\t=>\tFAIL\n");
        free(mallocPtr);
        return;
    }

    free(mallocPtr);
    printf("3)MyMallocInit\t=>\tPASS\n");
}

static void MyMallocT1()
{
    void *MyMallocT;

    if ((MyMallocT = MyMalloc(NULL, 72)) == NULL)
    {
        printf("1)MyMalloc\t=>\tPASS\n");
        return;
    }

    printf("1)MyMalloc\t=>\tFAIL\n");
}

static void MyMallocT2()
{
    void *mallocPtr, *MyMallocT;

    if ((mallocPtr = (void *)malloc(10000)) == NULL)
    {
        printf("2)MyMalloc\t=>\tmalloc fail\n");
        return;
    }

    MyMallocInit(mallocPtr, 28);

    if ((MyMallocT = MyMalloc(mallocPtr, 0)) == NULL)
    {
        printf("2)MyMalloc\t=>\tPASS\n");
        free(mallocPtr);
        return;
    }

    printf("2)MyMalloc\t=>\tFAIL\n");
    free(mallocPtr);
}

/*Negative test: _requiredBlockSize alignment */
static void MyMallocT3()
{
    void *mallocPtr, *MyMallocT;

    if ((mallocPtr = (void *)malloc(10000)) == NULL)
    {
        printf("3)MyMalloc\t=>\tmalloc fail\n");
        return;
    }

    MyMallocInit(mallocPtr, 28);

    if ((MyMallocT = MyMalloc(mallocPtr, 2)) == NULL)
    {
        printf("3)MyMalloc\t=>\tPASS\n");
        free(mallocPtr);
        return;
    }

    printf("3)MyMalloc\t=>\tFAIL\n");
    free(mallocPtr);
}

/*Negative test: _requiredBlockSize > _memorySize */
static void MyMallocT4()
{
    void *mallocPtr, *MyMallocT;

    if ((mallocPtr = (void *)malloc(10000)) == NULL)
    {
        printf("4)MyMalloc\t=>\tmalloc fail\n");
        return;
    }

    MyMallocInit(mallocPtr, 28);

    if ((MyMallocT = MyMalloc(mallocPtr, 30)) == NULL)
    {
        printf("4)MyMalloc\t=>\tPASS\n");
        free(mallocPtr);
        return;
    }

    printf("4)MyMalloc\t=>\tFAIL\n");
    free(mallocPtr);
}

/*Negative test: _requiredBlockSize > _memorySize */
static void MyMallocT5()
{
    void *mallocPtr, *MyMallocT;

    if ((mallocPtr = (void *)malloc(10000)) == NULL)
    {
        printf("5)MyMalloc\t=>\tmalloc fail\n");
        return;
    }

    MyMallocInit(mallocPtr, 100);
    MyMallocT = MyMalloc(mallocPtr, 40);
    if (MyMallocT != NULL && METADATA_AT_INDEX(MyMallocT, 0) == -40)
    {
        printf("5)MyMalloc\t=>\tPASS\n");
        free(mallocPtr);
        return;
    }

    printf("5)MyMalloc\t=>\tFAIL\n");
    free(mallocPtr);
}

/*Positive test:  _requiredBlockSize + alignment*/
static void MyMallocT6()
{
    void *mallocPtr, *MyMallocT;

    if ((mallocPtr = (void *)malloc(10000)) == NULL)
    {
        printf("6)MyMalloc\t=>\tmalloc fail\n");
        return;
    }

    MyMallocInit(mallocPtr, 100);
    MyMallocT = MyMalloc(mallocPtr, 41);

    if (MyMallocT != NULL && METADATA_AT_INDEX(MyMallocT, 0) == -48)
    {
        printf("6)MyMalloc\t=>\tPASS\n");
        free(mallocPtr);
        return;
    }

    printf("6)MyMalloc\t=>\tFAIL\n");
    free(mallocPtr);
}

/*Positive test:  _requiredBlockSize + alignment*/
static void MyMallocT7()
{
    void *mallocPtr, *MyMallocT1, *MyMallocT2, *MyMallocT3;

    if ((mallocPtr = (void *)malloc(10000)) == NULL)
    {
        printf("7)MyMalloc\t=>\tmalloc fail\n");
        return;
    }

    MyMallocInit(mallocPtr, 1000);
    MyMallocT1 = MyMalloc(mallocPtr, 40);
    MyMallocT2 = MyMalloc(mallocPtr, 80);
    MyMallocT3 = MyMalloc(mallocPtr, 117);

    if (MyMallocT1 != NULL && METADATA_AT_INDEX(MyMallocT1, 0) == -40)
    {
        if (MyMallocT2 != NULL && METADATA_AT_INDEX(MyMallocT2, 0) == -80)
        {
            if (MyMallocT3 != NULL && METADATA_AT_INDEX(MyMallocT3, 0) == -120)
            {
                printf("7)MyMalloc\t=>\tPASS\n");
                free(mallocPtr);
                return;
            }
        }
    }

    printf("7)MyMalloc\t=>\tFAIL\n");
    free(mallocPtr);
}

static void MyFreeT1()
{
    MyFree(NULL);
    printf("1)MyFree\t=>\tPASS\n");
}

static void MyFreeT2()
{
    void *mallocPtr, *MyMallocT;

    if ((mallocPtr = (void *)malloc(10000)) == NULL)
    {
        printf("5)MyMalloc\t=>\tmalloc fail\n");
        return;
    }

    MyMallocInit(mallocPtr, 100);
    MyMallocT = MyMalloc(mallocPtr, 20);

    MyFree(MyMallocT);

    if (METADATA_AT_INDEX(MyMallocT, 0) > 0)
    {
        printf("5)MyMalloc\t=>\tPASS\n");
        free(mallocPtr);
        return;
    }

    printf("5)MyMalloc\t=>\tFAIL\n");
    free(mallocPtr);
}

static void MyFreeT3()
{
    void *mallocPtr, *MyMallocT;

    if ((mallocPtr = (void *)malloc(10000)) == NULL)
    {
        printf("5)MyMalloc\t=>\tmalloc fail\n");
        return;
    }

    MyMallocInit(mallocPtr, 100);
    MyMallocT = MyMalloc(mallocPtr, 20);

    MyFree(MyMallocT);
    MyFree(MyMallocT);

    if (METADATA_AT_INDEX(MyMallocT, 0) > 0)
    {
        printf("5)MyMalloc\t=>\tPASS\n");
        free(mallocPtr);
        return;
    }

    printf("5)MyMalloc\t=>\tFAIL\n");
    free(mallocPtr);
}

static void MyFreeT4()
{
    void *mallocPtr, *MyMallocT1, *MyMallocT2, *MyMallocT3;

    if ((mallocPtr = (void *)malloc(10000)) == NULL)
    {
        printf("7)MyMalloc\t=>\tmalloc fail\n");
        return;
    }

    MyMallocInit(mallocPtr, 1000);
    MyMallocT1 = MyMalloc(mallocPtr, 40);
    MyMallocT2 = MyMalloc(mallocPtr, 80);
    MyMallocT3 = MyMalloc(mallocPtr, 120);

    MyFree(MyMallocT3);
    printf("METADATA_AT_INDEX(MyMallocT, 0):%d\n", METADATA_AT_INDEX(MyMallocT3, 0));

    MyFree(MyMallocT2);
    printf("METADATA_AT_INDEX(MyMallocT, 0):%d\n", METADATA_AT_INDEX(MyMallocT2, 0));

    MyFree(MyMallocT1);
    printf("METADATA_AT_INDEX(MyMallocT, 0):%d\n", METADATA_AT_INDEX(MyMallocT1, 0));

    printf("7)MyMalloc\t=>\tFAIL\n");
    free(mallocPtr);
}
