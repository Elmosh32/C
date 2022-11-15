/**********************************************************************************
                                includes && define
**********************************************************************************/
#include <stdio.h>  /* printf */
#include <stdlib.h> /* free */

#include "genHashSet.h" /* Hash  Set Header */

/**********************************************************************************
                     Declaration of static test Functions
**********************************************************************************/
static void HastCreateT1();
static void HastCreateT2();
static void HastCreateT3();

static void HashDestroyT1();
static void HashDestroyT2();
static void HashDestroyT3();
static void HashDestroyT4();

static void HastInsertT1();
static void HastInsertT2();
static void HastInsertT3();
static void HastInsertT4();
static void HastInsertT5();
static void HastInsertT6();

void FreeElement(void *_data)
{
    free(_data);
    return;
}

size_t HashFunc(void *_element)
{
    return ((*(int *)_element + 1) * 5);
}

int EqualityFunc(void *_item1, void *_item2)
{
    if (*(int *)_item1 == *(int *)_item2)
    {
        return 1;
    }

    return 0;
}

void PrintElement(void *_element)
{
    printf("%d=>\t", *(int *)_element);
}

int main(void)
{
    printf("\n*************************************************************\n"
           "                     createTree tests\n"
           "*************************************************************\n");
    HastCreateT1();
    HastCreateT2();
    HastCreateT3();

    printf("\n*************************************************************\n"
           "                     HashDestroy tests\n"
           "*************************************************************\n");
    HashDestroyT1();
    HashDestroyT2();
    HashDestroyT3();
    HashDestroyT4();
    printf("\n*************************************************************\n"
           "                     HashInsert tests\n"
           "*************************************************************\n");
    HastInsertT1();
    HastInsertT2();
    HastInsertT3();
    HastInsertT4();
    HastInsertT5();
    HastInsertT6();

    return 0;
}

/**************************************************************
                        HashCreate tests
***************************************************************/
static void HastCreateT1()
{
    Hash *hash = NULL;

    if ((hash = HashCreate(4, HashFunc, EqualityFunc)) == NULL)
    {
        printf("(1) HashCreate test\t=>\tFAIL\n");
    }
    else
    {
        printf("(1) HashCreate test\t=>\tPASS\n");
    }

    HashDestroy(&hash, NULL);
}

static void HastCreateT2()
{
    Hash *hash = NULL;

    if ((hash = HashCreate(4, NULL, EqualityFunc)) != NULL)
    {
        printf("(2) HashCreate test\t=>\tFAIL\n");
    }
    else
    {
        printf("(2) HashCreate test\t=>\tPASS\n");
    }

    HashDestroy(&hash, NULL);
}

static void HastCreateT3()
{
    Hash *hash = NULL;

    if ((hash = HashCreate(4, HashFunc, NULL)) != NULL)
    {
        printf("(3) HashCreate test\t=>\tFAIL\n");
    }
    else
    {
        printf("(3) HashCreate test\t=>\tPASS\n");
    }
    HashDestroy(&hash, NULL);
}

/**************************************************************
                        HashDestroy tests
***************************************************************/
static void HashDestroyT1()
{
    HashDestroy(NULL, NULL);
    printf("(1) HashDestroy test\t=>\tPASS\n");
}

static void HashDestroyT2()
{
    Hash *hash = NULL;
    hash = HashCreate(5, HashFunc, EqualityFunc);

    HashDestroy(&hash, NULL);
    HashDestroy(&hash, NULL);
    printf("(2) HashDestroy test\t=>\tPASS\n");
}

static void HashDestroyT3()
{
    Hash *hash = NULL;
    int *a[5];

    hash = HashCreate(8, HashFunc, EqualityFunc);

    a[0] = malloc(sizeof(int));
    *a[0] = 4;
    HashInsert(hash, (void *)a[0]);

    a[1] = malloc(sizeof(int));
    *a[1] = 5;
    HashInsert(hash, (void *)a[1]);

    a[2] = malloc(sizeof(int));
    *a[2] = 2;
    HashInsert(hash, (void *)a[2]);

    a[3] = malloc(sizeof(int));
    *a[3] = 1;
    HashInsert(hash, (void *)a[3]);

    a[4] = malloc(sizeof(int));
    *a[4] = 3;
    HashInsert(hash, (void *)a[4]);

    HashDestroy(&hash, FreeElement);

    if (hash == NULL)
    {
        printf("(3) HashDestroy test\t=>\tPASS\n");
    }
    else
    {
        printf("(3) HashDestroy test\t=>\tFAIL\n");
    }
}

static void HashDestroyT4()
{
    HashDestroy(NULL, FreeElement);
    printf("(4) HashDestroy test\t=>\tPASS\n");
}

/**************************************************************
                        HashInsert tests
***************************************************************/
static void HastInsertT1()
{
    Hash *hash = NULL;
    int *a[5];

    hash = HashCreate(5, HashFunc, EqualityFunc);

    a[0] = malloc(sizeof(int));
    *a[0] = 4;
    HashInsert(hash, (void *)a[0]);

    a[1] = malloc(sizeof(int));
    *a[1] = 5;
    HashInsert(hash, (void *)a[1]);

    a[2] = malloc(sizeof(int));
    *a[2] = 2;
    HashInsert(hash, (void *)a[2]);

    a[3] = malloc(sizeof(int));
    *a[3] = 1;
    HashInsert(hash, (void *)a[3]);

    a[4] = malloc(sizeof(int));
    *a[4] = 3;

    if (HashInsert(hash, (void *)a[4]) == SET_SUCCESS)
    {
        printf("(1) HashInsert test\t=>\tPASS\n");
    }
    else
    {
        printf("(1) HashInsert test\t=>\tFAIL\n");
    }

    HashDestroy(&hash, NULL);
}

static void HastInsertT2()
{
    Hash *hash = NULL;
    int *a[5];

    hash = HashCreate(5, HashFunc, EqualityFunc);

    a[0] = malloc(sizeof(int));
    *a[0] = 4;
    HashInsert(hash, (void *)a[0]);

    a[1] = malloc(sizeof(int));
    *a[1] = 5;
    HashInsert(hash, (void *)a[1]);

    a[2] = malloc(sizeof(int));
    *a[2] = 2;
    HashInsert(hash, (void *)a[2]);

    a[3] = malloc(sizeof(int));
    *a[3] = 1;
    HashInsert(hash, (void *)a[3]);

    if (HashInsert(hash, (void *)a[2]) == SET_KEY_DUPLICATE)
    {
        printf("(2) HashInsert test\t=>\tPASS\n");
    }
    else
    {
        printf("(2) HashInsert test\t=>\tFAIL\n");
    }

    HashDestroy(&hash, NULL);
}

static void HastInsertT3()
{
    Hash *hash = NULL;
    int *a[5];

    hash = HashCreate(3, HashFunc, EqualityFunc);

    a[0] = malloc(sizeof(int));
    *a[0] = 4;
    HashInsert(hash, (void *)a[0]);

    a[1] = malloc(sizeof(int));
    *a[1] = 5;
    HashInsert(hash, (void *)a[1]);

    a[2] = malloc(sizeof(int));
    *a[2] = 2;
    HashInsert(hash, (void *)a[2]);

    a[3] = malloc(sizeof(int));
    *a[3] = 1;
    HashInsert(hash, (void *)a[3]);

    a[4] = malloc(sizeof(int));
    *a[4] = 11;

    if ((HashInsert(hash, (void *)a[4])) == SET_OVERFLOW)
    {
        printf("(3) HashInsert test\t=>\tPASS\n");
    }
    else
    {
        printf("(3) HashInsert test\t=>\tFAIL\n");
    }

    HashDestroy(&hash, NULL);
}

static void HastInsertT4()
{
    Hash *hash = NULL;
    int *a[5];

    hash = HashCreate(3, HashFunc, EqualityFunc);

    a[0] = malloc(sizeof(int));
    *a[0] = 4;
    HashInsert(hash, (void *)a[0]);

    if ((HashInsert(NULL, (void *)a[0])) == SET_UNINITIALIZED)
    {
        printf("(4) HashInsert test\t=>\tPASS\n");
    }
    else
    {
        printf("(4) HashInsert test\t=>\tFAIL\n");
    }

    HashDestroy(&hash, NULL);
}

static void HastInsertT5()
{
    Hash *hash = NULL;

    hash = HashCreate(3, HashFunc, EqualityFunc);

    if ((HashInsert(hash, NULL) == SET_UNINITIALIZED))
    {
        printf("(5) HashInsert test\t=>\tPASS\n");
    }
    else
    {
        printf("(5) HashInsert test\t=>\tFAIL\n");
    }

    HashDestroy(&hash, NULL);
}

static void HastInsertT6()
{

    if ((HashInsert(NULL, NULL)) == SET_UNINITIALIZED)
    {
        printf("(3) HashInsert test\t=>\tPASS\n");
    }
    else
    {
        printf("(3) HashInsert test\t=>\tFAIL\n");
    }
}
