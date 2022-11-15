/**********************************************************************************
                                includes
**********************************************************************************/
#include <stdio.h>  /*printf*/
#include <stdlib.h> /*free*/
#include <string.h> /*strlen & strcmp*/

#include "../hash/hashMap/genHashMap.h"
#include "../genDoubleList/list_functions.h"
#include "../genDoubleList/genDoubleList.h"
#include "../genDoubleList/list_itr.h"

/**********************************************************************************
                                Person struct
**********************************************************************************/
typedef struct Person Person;

struct Person
{
    int m_id;
    char m_name[20];
    int m_age;
};

/**********************************************************************************
                                global arrays
**********************************************************************************/
Person person[10] = {{1, "lior", 21}, {2, "yakov", 31}, {3, "michal", 46}, {4, "adir", 34}, {5, "eli", 55}, {6, "elior", 30}, {35, "shmuel", 21}, {8, "yakir", 31}, {17, "rita", 46}, {23, "yuval", 21}};
char words[10][100] = {"Random", "string", "test", "for", "main", "Hash", "Map", "Test", "file", "=>Pass"};
Person students[10] = {{1, "lior", 21}, {2, "yakov", 31}, {3, "michal", 46}, {4, "adir", 34}, {5, "eli", 55}, {6, "elior", 30}, {35, "shmuel", 21}, {8, "yakir", 31}, {17, "rita", 46}, {23, "yuval", 21}};
int keys[] = {93, 21, 4, 7, 32, 1, 1550, 54, 222, 100, 23, 310};
int values[] = {0, 1, 223, 36, 447, 50, 62, 711, 8888, 9, 1000, 11};
int duplicateKeys[] = {93, 21, 4, 7, 32, 1, 1550, 54, 222, 100, 32, 310};
int floatKeys[] = {93.1, 21, 4.999, 7.0, 32.32, 1, 1550, 54, 222.44, 100.100, 32, 310};

/**********************************************************************************
                    Equality Functions used in HashMap_Create
**********************************************************************************/
int CompareInt(void *_firstKey, void *_secondKey)
{
    return *(int *)_firstKey == *(int *)_secondKey;
}

int CompareStrings(void *_firstKey, void *_secondKey)
{
    return strcmp((char *)_firstKey, (char *)_secondKey);
}

/**********************************************************************************
                    Hash functions used in HashMap_Create
**********************************************************************************/
size_t IntHashFunc(const void *_element)
{
    return (size_t)((*(int *)_element + 1) * 5);
}

size_t StringHashFunc(const void *_element)
{
    size_t hash = 0, i;
    int length = strlen((char *)_element);
    char *word = (char *)malloc(length * sizeof(char));

    strcpy(word, (char *)_element);

    for (i = 0; i < length; i++)
    {
        hash = hash + *(word + i);
    }

    free(word);
    return hash;
}

/**********************************************************************************
                    KeyValueActionFunction used in HashMap_ForEach
**********************************************************************************/
int PrintIntHash(const void *_key, void *_value, void *_context)
{
    printf("key = %d\t value = %d\n", *(int *)_key, *(int *)_value);
    return 1;
}

int PrintPersonHash(const void *_key, void *_value, void *_context)
{
    printf("person id = %d\t  person name = %s\t  person age = %d\n", (*(Person *)_key).m_id, (*(Person *)_key).m_name, (*(Person *)_key).m_age);
    return 1;
}

int PrintStingHash(const void *_key, void *_value, void *_context)
{
    printf("Key and string val:%s\n", ((char *)_value));
    return 1;
}

int HashForEach(const void *_key, void *_value, void *_context)
{
    return 1;
}

/**********************************************************************************
                _keyDestroy & _valDestroy used in HashMap_Destroy
**********************************************************************************/
void FreeKey(void *_key)
{
    free(_key);
}

void FreeVal(void *_value)
{
    free(_value);
}

/**********************************************************************************
                   Declaration of static test functions
**********************************************************************************/
static void HashMap_CreateT1();
static void HashMap_CreateT2();
static void HashMap_CreateT3();
static void HashMap_CreateT4();
static void HashMap_CreateT5();

static void HashMap_DestroyT1();
static void HashMap_DestroyT2();
static void HashMap_DestroyT3();
static void HashMap_DestroyT4();

static void HashMap_InsertT1();
static void HashMap_InsertT2();
static void HashMap_InsertT3();
static void HashMap_InsertT4();
static void HashMap_InsertT5();
static void HashMap_InsertT6();

static void HashMap_RemoveT1();
static void HashMap_RemoveT2();
static void HashMap_RemoveT3();
static void HashMap_RemoveT4();
static void HashMap_RemoveT5();

static void HashMap_FindT1();
static void HashMap_FindT2();
static void HashMap_FindT3();
static void HashMap_FindT4();
static void HashMap_FindT5();

static void HashMap_SizeT1();
static void HashMap_SizeT2();
static void HashMap_SizeT3();

static void HashMap_ForEachT1();
static void HashMap_ForEachT2();
static void HashMap_ForEachT3();

int HashMapTest()
{
    printf("\n*************************************************************\n"
           "                     HashMap_Create tests\n"
           "*************************************************************\n");
    HashMap_CreateT1();
    HashMap_CreateT2();
    HashMap_CreateT3();
    HashMap_CreateT4();
    HashMap_CreateT5();

    printf("\n*************************************************************\n"
           "                     HashMap_Destroy tests\n"
           "*************************************************************\n");
    HashMap_DestroyT1();
    HashMap_DestroyT2();
    HashMap_DestroyT3();
    HashMap_DestroyT4();

    printf("\n*************************************************************\n"
           "                     HashMap_Insert tests\n"
           "*************************************************************\n");
    HashMap_InsertT1();
    HashMap_InsertT2();
    HashMap_InsertT3();
    HashMap_InsertT4();
    HashMap_InsertT5();
    HashMap_InsertT6();

    printf("\n*************************************************************\n"
           "                     HashMap_Remove tests\n"
           "*************************************************************\n");
    HashMap_RemoveT1();
    HashMap_RemoveT2();
    HashMap_RemoveT3();
    HashMap_RemoveT4();
    HashMap_RemoveT5();

    printf("\n*************************************************************\n"
           "                     HashMap_Find tests\n"
           "*************************************************************\n");
    HashMap_FindT1();
    HashMap_FindT2();
    HashMap_FindT3();
    HashMap_FindT4();
    HashMap_FindT5();

    printf("\n*************************************************************\n"
           "                     HashMap_Size tests\n"
           "*************************************************************\n");
    HashMap_SizeT1();
    HashMap_SizeT2();
    HashMap_SizeT3();

    printf("\n*************************************************************\n"
           "                     HashMap_ForEach tests\n"
           "*************************************************************\n");
    HashMap_ForEachT1();
    HashMap_ForEachT2();
    HashMap_ForEachT3();

    return 0;
}

/*********************************************************************************
**********************************************************************************
                             test functions
**********************************************************************************
**********************************************************************************/

/**************************************************************
                    HashMap_Create tests
***************************************************************/
static void HashMap_CreateT1()
{
    HashMap *hash;

    hash = HashMap_Create(10, NULL, NULL);
    if (hash != NULL)
    {
        printf("(1) HashMap_Create test\t=>\tFAIL\n");
    }
    else
    {
        printf("(1) HashMap_Create test\t=>\tPASS\n");
    }

    HashMap_Destroy(&hash, NULL, NULL);
}

static void HashMap_CreateT2()
{
    HashMap *hash;

    hash = HashMap_Create(10, NULL, CompareInt);
    if (hash != NULL)
    {
        printf("(2) HashMap_Create test\t=>\tFAIL\n");
    }
    else
    {
        printf("(2) HashMap_Create test\t=>\tPASS\n");
    }

    HashMap_Destroy(&hash, NULL, NULL);
}

static void HashMap_CreateT3()
{
    HashMap *hash;

    hash = HashMap_Create(10, IntHashFunc, NULL);
    if (hash != NULL)
    {
        printf("(3) HashMap_Create test\t=>\tFAIL\n");
    }
    else
    {
        printf("(3) HashMap_Create test\t=>\tPASS\n");
    }

    HashMap_Destroy(&hash, NULL, NULL);
}

static void HashMap_CreateT4()
{
    HashMap *hash;

    hash = HashMap_Create(9, IntHashFunc, CompareInt);
    if (hash != NULL)
    {
        printf("(4) HashMap_Create test\t=>\tFAIL\n");
    }
    else
    {
        printf("(4) HashMap_Create test\t=>\tPASS\n");
    }

    HashMap_Destroy(&hash, NULL, NULL);
}

static void HashMap_CreateT5()
{
    HashMap *hash;

    hash = HashMap_Create(10, IntHashFunc, CompareInt);
    if (hash == NULL)
    {
        printf("(5) HashMap_Create test\t=>\tFAIL\n");
    }
    else
    {
        printf("(5) HashMap_Create test\t=>\tPASS\n");
    }

    HashMap_Destroy(&hash, NULL, NULL);
}

/**************************************************************
                    HashMap_Destroy tests
***************************************************************/
static void HashMap_DestroyT1()
{
    HashMap_Destroy(NULL, NULL, NULL);
    printf("(1) HashMap_Destroy test\t=>\tPASS\n");
}

/* TreeCreate NEGATIVE TEST => BSTreeDestroy TWICE*/
static void HashMap_DestroyT2()
{
    HashMap *hash;
    hash = HashMap_Create(10, IntHashFunc, CompareInt);
    HashMap_Destroy(&hash, FreeKey, FreeVal);
    HashMap_Destroy(&hash, FreeKey, FreeVal);
    printf("(2) HashMap_Destroy test\t=>\tPASS\n");
}

static void HashMap_DestroyT3()
{
    HashMap *hash;
    int *arr1[12], *arr2[12];
    size_t i;

    hash = HashMap_Create(10, IntHashFunc, CompareInt);

    for (i = 0; i < 12; i++)
    {
        arr1[i] = malloc(sizeof(int));
        arr2[i] = malloc(sizeof(int));
        *arr1[i] = keys[i];
        *arr2[i] = values[i];
        HashMap_Insert(hash, arr1[i], arr2[i]);
    }

    HashMap_Destroy(&hash, FreeKey, FreeVal);
    HashMap_Destroy(&hash, FreeKey, FreeVal);
    printf("(3) HashMap_Destroy test\t=>\tPASS\n");
}

static void HashMap_DestroyT4()
{
    HashMap *hash;
    int *arr1[12], *arr2[12];
    size_t i;

    hash = HashMap_Create(10, IntHashFunc, CompareInt);

    for (i = 0; i < 12; i++)
    {
        arr1[i] = malloc(sizeof(int));
        arr2[i] = malloc(sizeof(int));
        *arr1[i] = keys[i];
        *arr2[i] = values[i];
        HashMap_Insert(hash, arr1[i], arr2[i]);
    }

    HashMap_Destroy(&hash, FreeKey, FreeVal);
    printf("(4) HashMap_Destroy test\t=>\tPASS\n");
}

/**************************************************************
                    HashMap_Insert tests
***************************************************************/
static void HashMap_InsertT1()
{
    int *arr1[1], *arr2[1];

    arr1[0] = malloc(sizeof(int));
    arr2[0] = malloc(sizeof(int));
    *arr1[0] = keys[0];
    *arr2[0] = values[0];

    if ((HashMap_Insert(NULL, arr1[0], arr2[0])) == MAP_UNINITIALIZED_ERROR)
    {
        printf("(1) HashMap_Insert test\t=>\tPASS\n");
    }
    else
    {
        printf("(1) HashMap_Insert test\t=>\tFAIL\n");
    }
    free(arr1[0]);
    free(arr2[0]);
}

static void HashMap_InsertT2()
{
    HashMap *hash;
    int *val;

    hash = HashMap_Create(10, IntHashFunc, CompareInt);
    val = malloc(sizeof(int));

    *val = 3;

    if ((HashMap_Insert(hash, NULL, val)) == MAP_KEY_NULL_ERROR)
    {
        printf("(2) HashMap_Insert test\t=>\tPASS\n");
    }
    else
    {
        printf("(2) HashMap_Insert test\t=>\tFAIL\n");
    }

    free(val);
    HashMap_Destroy(&hash, FreeKey, FreeVal);
}

static void HashMap_InsertT3()
{
    HashMap *hash;
    int *keysArr[12], *valsArr[12];
    int i;

    hash = HashMap_Create(12, IntHashFunc, CompareInt);

    for (i = 0; i < 12; i++)
    {
        keysArr[i] = malloc(sizeof(int));
        valsArr[i] = malloc(sizeof(int));
        *keysArr[i] = duplicateKeys[i];
        *valsArr[i] = values[i];

        if ((HashMap_Insert(hash, keysArr[i], valsArr[i])) == MAP_KEY_DUPLICATE_ERROR)
        {
            printf("(3) HashMap_Insert test\t=>\tPASS\n");
            HashMap_Destroy(&hash, FreeKey, FreeVal);
            return;
        }
    }

    printf("(3) HashMap_Insert test\t=>\tFAIL\n");

    HashMap_Destroy(&hash, FreeKey, FreeVal);
}

static void HashMap_InsertT4()
{
    HashMap *hash;
    int *keysArr[12], *valsArr[12];
    int i;

    hash = HashMap_Create(12, IntHashFunc, CompareInt);

    for (i = 0; i < 12; i++)
    {
        keysArr[i] = malloc(sizeof(int));
        valsArr[i] = malloc(sizeof(int));
        *keysArr[i] = keys[i];
        *valsArr[i] = values[i];

        if ((HashMap_Insert(hash, keysArr[i], valsArr[i])) != MAP_SUCCESS)
        {
            printf("(4) HashMap_Insert test\t=>\tFAIL\n");
            HashMap_Destroy(&hash, FreeKey, FreeVal);
            return;
        }
    }

    printf("(4) HashMap_Insert test\t=>\tPASS\n");
    HashMap_Destroy(&hash, FreeKey, FreeVal);
}

static void HashMap_InsertT5()
{
    HashMap *hash;
    int *keysArr[10];
    Person *valsArr[10];
    int i;

    hash = HashMap_Create(10, IntHashFunc, CompareInt);

    for (i = 0; i < 10; i++)
    {
        keysArr[i] = malloc(sizeof(int));
        valsArr[i] = malloc(sizeof(Person));
        *keysArr[i] = person[i].m_id;
        *valsArr[i] = person[i];

        if ((HashMap_Insert(hash, keysArr[i], valsArr[i])) != MAP_SUCCESS)
        {
            printf("(5) HashMap_Insert test\t=>\tFAIL\n");
            HashMap_Destroy(&hash, FreeKey, FreeVal);
            return;
        }
    }

    printf("(5) HashMap_Insert test\t=>\tPASS\n");
    HashMap_Destroy(&hash, FreeKey, FreeVal);
}

static void HashMap_InsertT6()
{
    HashMap *hash;
    char *keysArr[10], *valsArr[10];
    int i;

    hash = HashMap_Create(10, StringHashFunc, CompareInt);

    for (i = 0; i < 10; i++)
    {
        keysArr[i] = malloc(sizeof(char *));
        valsArr[i] = malloc(sizeof(char *));
        strcpy(keysArr[i], words[i]);
        strcpy(valsArr[i], words[i]);

        if ((HashMap_Insert(hash, keysArr[i], valsArr[i])) != MAP_SUCCESS)
        {
            printf("(6) HashMap_Insert test\t=>\tFAIL\n");
            HashMap_Destroy(&hash, FreeKey, FreeVal);
            return;
        }
    }

    printf("(6) HashMap_Insert test\t=>\tPASS\n");
    HashMap_Destroy(&hash, FreeKey, FreeVal);
}

/**************************************************************
                    HashMap_Remove tests
***************************************************************/
static void HashMap_RemoveT1()
{
    HashMap *hash;
    void *key = NULL;
    void *value = NULL;

    hash = HashMap_Create(10, IntHashFunc, CompareInt);
    if ((HashMap_Remove(hash, &keys[2], &key, &value)) == MAP_EMPTY_ERROR)
    {
        printf("(1) HashMap_Remove test\t=>\tPASS\n");
    }
    else
    {
        printf("(1) HashMap_Remove test\t=>\tFAIL\n");
    }

    HashMap_Destroy(&hash, NULL, NULL);
}

static void HashMap_RemoveT2()
{
    void *key = NULL;
    void *value = NULL;

    if ((HashMap_Remove(NULL, &keys[2], &key, &value)) == MAP_UNINITIALIZED_ERROR)
    {
        printf("(2) HashMap_Remove test\t=>\tPASS\n");
    }
    else
    {
        printf("(2) HashMap_Remove test\t=>\tFAIL\n");
    }
}

static void HashMap_RemoveT3()
{
    HashMap *hash;
    int *arr1[10], *arr2[10];
    size_t i;
    void *key = NULL;
    void *value = NULL;

    hash = HashMap_Create(10, IntHashFunc, CompareInt);

    for (i = 0; i < 10; i++)
    {
        arr1[i] = malloc(sizeof(int));
        arr2[i] = malloc(sizeof(int));
        *arr1[i] = keys[i];
        *arr2[i] = values[i];
        HashMap_Insert(hash, arr1[i], arr2[i]);
    }

    if ((HashMap_Remove(hash, &keys[10], &key, &value)) == MAP_KEY_NOT_FOUND_ERROR)
    {
        printf("(3) HashMap_Remove test\t=>\tPASS\n");
    }
    else
    {
        printf("(3) HashMap_Remove test\t=>\tFAIL\n");
    }

    HashMap_Destroy(&hash, FreeKey, FreeVal);
}
static void HashMap_RemoveT4()
{
    HashMap *hash;
    int *arr1[12], *arr2[12];
    size_t i;
    void *key = NULL;
    void *value = NULL;

    hash = HashMap_Create(10, IntHashFunc, CompareInt);

    for (i = 0; i < 12; i++)
    {
        arr1[i] = malloc(sizeof(int));
        arr2[i] = malloc(sizeof(int));
        *arr1[i] = keys[i];
        *arr2[i] = values[i];
        HashMap_Insert(hash, arr1[i], arr2[i]);
    }

    if ((HashMap_Remove(hash, NULL, &key, &value)) == MAP_KEY_NULL_ERROR)
    {
        printf("(4) HashMap_Remove test\t=>\tPASS\n");
    }
    else
    {
        printf("(4) HashMap_Remove test\t=>\tFAIL\n");
    }

    HashMap_Destroy(&hash, FreeKey, FreeVal);
}

static void HashMap_RemoveT5()
{
    HashMap *hash;
    int *arr1[12], *arr2[12];
    size_t i;
    void *key = NULL;
    void *value = NULL;

    hash = HashMap_Create(10, IntHashFunc, CompareInt);

    for (i = 0; i < 12; i++)
    {
        arr1[i] = malloc(sizeof(int));
        arr2[i] = malloc(sizeof(int));
        *arr1[i] = keys[i];
        *arr2[i] = values[i];
        HashMap_Insert(hash, arr1[i], arr2[i]);
    }

    if ((HashMap_Remove(hash, &keys[4], &key, &value)) == MAP_SUCCESS)
    {
        printf("(5) HashMap_Remove test\t=>\tPASS\n");
    }
    else
    {
        printf("(5) HashMap_Remove test\t=>\tFAIL\n");
    }

    HashMap_Destroy(&hash, FreeKey, FreeVal);
}

/**************************************************************
                    HashMap_Find tests
***************************************************************/
static void HashMap_FindT1()
{
    HashMap *hash;
    void *value = NULL;

    hash = HashMap_Create(10, IntHashFunc, CompareInt);
    if ((HashMap_Find(hash, &keys[2], value)) == MAP_EMPTY_ERROR)
    {
        printf("(1) HashMap_Find test\t=>\tPASS\n");
    }
    else
    {
        printf("(1) HashMap_Find test\t=>\tFAIL\n");
    }

    HashMap_Destroy(&hash, NULL, NULL);
}

static void HashMap_FindT2()
{
    void *value = NULL;

    if ((HashMap_Find(NULL, &keys[2], &value)) == MAP_UNINITIALIZED_ERROR)
    {
        printf("(2) HashMap_Find test\t=>\tPASS\n");
    }
    else
    {
        printf("(2) HashMap_Find test\t=>\tFAIL\n");
    }
}

static void HashMap_FindT3()
{
    HashMap *hash;
    int *arr1[10], *arr2[10];
    size_t i;
    void *value = NULL;

    hash = HashMap_Create(10, IntHashFunc, CompareInt);

    for (i = 0; i < 10; i++)
    {
        arr1[i] = malloc(sizeof(int));
        arr2[i] = malloc(sizeof(int));
        *arr1[i] = keys[i];
        *arr2[i] = values[i];
        HashMap_Insert(hash, arr1[i], arr2[i]);
    }

    if ((HashMap_Find(hash, &keys[10], &value)) == MAP_KEY_NOT_FOUND_ERROR)
    {
        printf("(3) HashMap_Find test\t=>\tPASS\n");
    }
    else
    {
        printf("(3) HashMap_Find test\t=>\tFAIL\n");
    }

    HashMap_Destroy(&hash, FreeKey, FreeVal);
}
static void HashMap_FindT4()
{
    HashMap *hash;
    int *arr1[12], *arr2[12];
    size_t i;
    void *value = NULL;

    hash = HashMap_Create(10, IntHashFunc, CompareInt);

    for (i = 0; i < 12; i++)
    {
        arr1[i] = malloc(sizeof(int));
        arr2[i] = malloc(sizeof(int));
        *arr1[i] = keys[i];
        *arr2[i] = values[i];
        HashMap_Insert(hash, arr1[i], arr2[i]);
    }

    if ((HashMap_Find(hash, NULL, &value)) == MAP_KEY_NULL_ERROR)
    {
        printf("(4) HashMap_Find test\t=>\tPASS\n");
    }
    else
    {
        printf("(4) HashMap_Find test\t=>\tFAIL\n");
    }

    HashMap_Destroy(&hash, FreeKey, FreeVal);
}

static void HashMap_FindT5()
{
    HashMap *hash;
    int *arr1[12], *arr2[12];
    size_t i;
    void *value = NULL;

    hash = HashMap_Create(10, IntHashFunc, CompareInt);

    for (i = 0; i < 12; i++)
    {
        arr1[i] = malloc(sizeof(int));
        arr2[i] = malloc(sizeof(int));
        *arr1[i] = keys[i];
        *arr2[i] = values[i];
        HashMap_Insert(hash, arr1[i], arr2[i]);
    }

    if ((HashMap_Find(hash, &keys[4], &value)) == MAP_SUCCESS)
    {
        printf("(5) HashMap_Find test\t=>\tPASS\n");
    }
    else
    {
        printf("(5) HashMap_Find test\t=>\tFAIL\n");
    }

    HashMap_Destroy(&hash, FreeKey, FreeVal);
}

/**************************************************************
                    HashMap_Size tests
***************************************************************/
static void HashMap_SizeT1()
{
    if (HashMap_Size(NULL) == 0)
    {
        printf("(1) HashMap_Size test\t=>\tPASS\n");
    }
    else
    {
        printf("(1) HashMap_Size test\t=>\tFAIL\n");
    }
}

static void HashMap_SizeT2()
{
    HashMap *hash;

    hash = HashMap_Create(10, IntHashFunc, CompareInt);
    if (HashMap_Size(hash) == 0)
    {
        printf("(2) HashMap_Size test\t=>\tPASS\n");
    }
    else
    {
        printf("(2) HashMap_Size test\t=>\tFAIL\n");
    }

    HashMap_Destroy(&hash, NULL, NULL);
}

static void HashMap_SizeT3()
{
    HashMap *hash;
    int *arr1[12], *arr2[12];
    size_t i;

    hash = HashMap_Create(10, IntHashFunc, CompareInt);

    for (i = 0; i < 12; i++)
    {
        arr1[i] = malloc(sizeof(int));
        arr2[i] = malloc(sizeof(int));
        *arr1[i] = keys[i];
        *arr2[i] = values[i];
        HashMap_Insert(hash, arr1[i], arr2[i]);
    }

    if (HashMap_Size(hash) == 12)
    {
        printf("(3) HashMap_Size test\t=>\tPASS\n");
    }
    else
    {
        printf("(3) HashMap_Size test\t=>\tFAIL\n");
    }

    HashMap_Destroy(&hash, FreeKey, FreeVal);
}

/**************************************************************
                    HashMap_ForEach tests
***************************************************************/
static void HashMap_ForEachT1()
{
    if (HashMap_ForEach(NULL, HashForEach, NULL) == 0)
    {
        printf("(1) HashMap_ForEach test\t=>\tPASS\n");
    }
    else
    {
        printf("(1) HashMap_ForEach test\t=>\tFAIL\n");
    }
}

static void HashMap_ForEachT2()
{
    HashMap *hash;
    int *arr1[12], *arr2[12];
    size_t i;

    hash = HashMap_Create(10, IntHashFunc, CompareInt);

    for (i = 0; i < 12; i++)
    {
        arr1[i] = malloc(sizeof(int));
        arr2[i] = malloc(sizeof(int));
        *arr1[i] = keys[i];
        *arr2[i] = values[i];
        HashMap_Insert(hash, arr1[i], arr2[i]);
    }

    if (HashMap_ForEach(hash, NULL, NULL) == 0)
    {
        printf("(2) HashMap_ForEach test\t=>\tPASS\n");
    }
    else
    {
        printf("(2) HashMap_ForEach test\t=>\tFAIL\n");
    }

    HashMap_Destroy(&hash, FreeKey, FreeVal);
}

static void HashMap_ForEachT3()
{
    HashMap *hash;
    int *arr1[12], *arr2[12];
    size_t i;

    hash = HashMap_Create(10, IntHashFunc, CompareInt);

    for (i = 0; i < 12; i++)
    {
        arr1[i] = malloc(sizeof(int));
        arr2[i] = malloc(sizeof(int));
        *arr1[i] = keys[i];
        *arr2[i] = values[i];
        HashMap_Insert(hash, arr1[i], arr2[i]);
    }

    if (HashMap_ForEach(hash, HashForEach, NULL) == 12)
    {
        printf("(3) HashMap_ForEach test\t=>\tPASS\n");
    }
    else
    {
        printf("(3) HashMap_ForEach test\t=>\tFAIL\n");
    }

    HashMap_Destroy(&hash, FreeKey, FreeVal);
}
