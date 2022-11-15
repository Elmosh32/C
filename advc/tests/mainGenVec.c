/**********************************************************************************
                                includes
**********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../genVec/genVector.h"

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

void FreeIntElement(void *_element)
{
        free((int *)_element);
}

void FreeCharElement(void *_element)
{
        free((char *)_element);
}

void FreeString(void *_element)
{
        free((*(char **)_element));
}
/**********************************************************************************
                        print functions to different data types
**********************************************************************************/
int IntVecPrint(void *_element, size_t _index, void *_context)
{
        printf("%d ", *(int *)_element);
        return 1;
}

int CharVecPrint(void *_element, size_t _index, void *_context)
{
        printf("%c ", *(char *)_element);
        return 1;
}

int StringVecPrint(void *_element, size_t _index, void *_context)
{
        printf("%s ", *(char **)_element);
        return 1;
}

int PersonVecPrint(void *_element, size_t _index, void *_context)
{
        printf("person[%ld]:  id = %d  name = %s  age = %d\n", _index, ((Person *)_element)->m_id, ((Person *)_element)->m_name, ((Person *)_element)->m_age);
        return 1;
}

int IsIntExist(void *_element, size_t _index, void *_context)
{
        if (*((int *)_element) == *((int *)_context))
        {
                return 0;
        }

        return 1;
}

int IsCharExist(void *_element, size_t _index, void *_context)
{
        if (*((char *)_element) == *((char *)_context))
        {
                return 0;
        }

        return 1;
}

int IsStringExist(void *_element, size_t _index, void *_context)
{
        if (strcmp(((char *)_element), ((char *)_context)) == 0)
        {
                return 0;
        }

        return 1;
}

int IsPersonExist(void *_element, size_t _index, void *_context)
{
        if (((Person *)_element)->m_id == ((Person *)_context)->m_id)
        {
                return 0;
        }

        return 1;
}

/**********************************************************************************
                   Declaration of static test functions
**********************************************************************************/
static void vectorCreateTests();
static void vectorCreateT1();
static void vectorCreateT2();
static void vectorCreateT3();
static void vectorCreateT4();
static void vectorCreateT5();

static void vectorDestroyTest();
static void vectorDestroyT1();
static void vectorDestroyT2();

static void VectorAppendTest();
static void AppendNullVec();
static void AppendNullItem();
static void AppendWithIncrease();

static void VectorTypes();
static void IntVector();
static void CharVector();
static void StringVector();
static void PersonVector();

int VectorTest()
{
        VectorTypes();

        vectorCreateTests();

        vectorDestroyTest();

        VectorAppendTest();

        return 0;
}

/**********************************************************************************
                             test functions
**********************************************************************************/
static void VectorTypes()
{
        printf("\n*********************************************************************\n"
               "********************print and find different types********************\n"
               "*********************************************************************\n");
        IntVector();
        CharVector();
        StringVector();
        PersonVector();
}

static void IntVector()
{
        Vector *vec = NULL;
        int flag = 0;
        int *a[6];

        vec = VectorCreate(2, 3);

        a[0] = malloc(sizeof(int));
        *a[0] = 10;
        VectorAppend(vec, (void *)a[0]);

        a[1] = malloc(sizeof(int));
        *a[1] = 30;
        VectorAppend(vec, (void *)a[1]);

        a[2] = malloc(sizeof(int));
        *a[2] = 20;
        VectorAppend(vec, (void *)a[2]);

        a[3] = malloc(sizeof(int));
        *a[3] = 220;
        VectorAppend(vec, (void *)a[3]);

        a[4] = malloc(sizeof(int));
        *a[4] = 154;
        VectorAppend(vec, (void *)a[4]);

        a[5] = malloc(sizeof(int));
        *a[5] = 1;

        VectorForEach(vec, IntVecPrint, NULL);
        if (VectorForEach(vec, IsIntExist, (void *)a[3]) == 3)
        {
                printf("\n%d found.", *a[3]);
                flag++;
        }
        else
        {
                printf("\n%d not found.", *a[3]);
        }

        if (VectorForEach(vec, IsIntExist, (void *)a[5]) == VectorSize(vec))
        {
                printf("\n%d not found.\n", *a[5]);
                flag++;
        }
        else
        {
                printf("\n%d found.\n", *a[5]);
        }

        if (flag == 2)
        {
                printf("int vector test => pass\n\n");
        }
        else
        {
                printf("int vector test => fail\n\n");
        }

        free(a[5]);
        VectorDestroy(&vec, FreeIntElement);
}

static void CharVector()
{
        Vector *vec = NULL;
        int flag = 0;

        char *a[5];

        vec = VectorCreate(2, 3);

        a[0] = malloc(sizeof(char));
        *a[0] = 'a';
        VectorAppend(vec, (void *)a[0]);

        a[1] = malloc(sizeof(char));
        *a[1] = 'q';
        VectorAppend(vec, (void *)a[1]);

        a[2] = malloc(sizeof(char));
        *a[2] = 'E';
        VectorAppend(vec, (void *)a[2]);

        a[3] = malloc(sizeof(char));
        *a[3] = 't';

        a[4] = malloc(sizeof(char));
        *a[4] = 'E';
        VectorAppend(vec, (void *)a[4]);

        VectorForEach(vec, CharVecPrint, NULL);
        if (VectorForEach(vec, IsCharExist, (void *)a[1]) == 1)
        {
                printf("\n'%c' found.", *a[1]);
                flag++;
        }
        else
        {
                printf("\n'%c' not found.", *a[1]);
        }

        if (VectorForEach(vec, IsCharExist, (void *)a[3]) == VectorSize(vec))
        {
                printf("\n'%c' not found.\n", *a[3]);
                flag++;
        }
        else
        {
                printf("\n'%c' found.\n", *a[3]);
        }

        if (flag == 2)
        {
                printf("char vector test => pass\n\n");
        }
        else
        {
                printf("char vector test => fail\n\n");
        }

        free(a[3]);
        VectorDestroy(&vec, FreeCharElement);
}

static void StringVector()
{
        Vector *vec = NULL;

        char *a[5][40];
        int flag = 0, i;

        vec = VectorCreate(2, 3);

        for (i = 0; i < 6; i++)
        {
                *a[i] = malloc(sizeof(char *) * 40);
        }

        strcpy(*a[0], "random");
        strcpy(*a[1], "something");
        strcpy(*a[2], "test");
        strcpy(*a[3], "String");
        strcpy(*a[4], "Result");
        strcpy(*a[5], "str");

        VectorAppend(vec, a[1]);
        VectorAppend(vec, a[4]);
        VectorAppend(vec, a[3]);
        VectorAppend(vec, a[5]);
        VectorAppend(vec, a[0]);

        VectorForEach(vec, StringVecPrint, NULL);

        if (VectorForEach(vec, IsStringExist, (void *)a[4]) != VectorSize(vec))
        {
                printf("\n\"%s\" found", *a[4]);
                flag++;
        }
        else
        {
                printf("\n\"%s\" not found", *a[4]);
        }

        if (VectorForEach(vec, IsStringExist, (void *)a[2]) == VectorSize(vec))
        {
                printf("\n\"%s\" not found \n", *a[2]);
                flag++;
        }
        else
        {
                printf("\n\"%s\" found\n", *a[2]);
        }

        if (flag == 2)
        {
                printf("string vector test => pass\n\n");
        }
        else
        {
                printf("string vector test => fail\n\n");
        }

        free(*a[2]);
        VectorDestroy(&vec, FreeString);
}

static void PersonVector()
{
        Vector *vec = NULL;
        int flag = 0;
        Person *persons[4];
        Person person1 = {2210, "itzhak", 31};
        Person person2 = {3132, "israel", 21};
        Person person3 = {1811, "michel", 46};
        Person person4 = {5112, "gal", 21};

        persons[0] = malloc(sizeof(Person));
        *persons[0] = person1;

        persons[1] = malloc(sizeof(Person));
        *persons[1] = person2;

        persons[2] = malloc(sizeof(Person));
        *persons[2] = person3;

        persons[3] = malloc(sizeof(Person));
        *persons[3] = person4;

        vec = VectorCreate(5, 5);
        VectorAppend(vec, persons[0]);
        VectorAppend(vec, persons[1]);
        VectorAppend(vec, persons[2]);

        VectorForEach(vec, PersonVecPrint, NULL);
        if (VectorForEach(vec, IsPersonExist, persons[3]) != VectorSize(vec))
        {
                printf("Person id:%d found\n", persons[3]->m_id);
        }
        else
        {
                printf("Person id:%d not found\n", persons[3]->m_id);
                flag++;
        }

        if (VectorForEach(vec, IsPersonExist, persons[1]) != VectorSize(vec))
        {
                printf("Person id:%d found\n", persons[1]->m_id);
                flag++;
        }
        else
        {
                printf("Person id:%d not found\n", persons[1]->m_id);
        }

        if (flag == 2)
        {
                printf("person vector test => pass\n\n");
        }
        else
        {
                printf("person vector test => fail\n\n");
        }

        free(persons[3]);
        VectorDestroy(&vec, FreeIntElement);
}

static void vectorCreateTests()
{
        printf("\n*********************************************************************\n"
               "***********************vector create tests***************************\n"
               "*********************************************************************\n");
        vectorCreateT1();
        vectorCreateT2();
        vectorCreateT3();
        vectorCreateT4();
        vectorCreateT5();
}

static void vectorCreateT1()
{
        Vector *vec = NULL;

        if ((vec = VectorCreate(1, 2)) != NULL)
        {
                printf("|VectorCreate(1,2)|\tVectorCreate POSITIVE test => pass\n");
        }
        else
        {
                printf("|VectorCreate(1,2)|\tVectorCreate POSITIVE test => fail\n");
        }

        VectorDestroy(&vec, NULL);
}

static void vectorCreateT2()
{
        Vector *vec;

        if ((vec = VectorCreate(2, 0)) != NULL)
        {
                printf("|VectorCreate(2,0)|\tVectorCreate POSITIVE test => pass\n");
        }
        else
        {
                printf("|VectorCreate(2,0)|\tVectorCreate POSITIVE test => fail\n");
        }

        VectorDestroy(&vec, NULL);
}

static void vectorCreateT3()
{
        Vector *vec;

        if ((vec = VectorCreate(0, 2)) != NULL)
        {
                printf("|VectorCreate(0,2)|\tVectorCreate POSITIVE test => pass\n");
        }
        else
        {
                printf("|VectorCreate(0,2)|\tVectorCreate POSITIVE test => fail\n");
        }

        VectorDestroy(&vec, NULL);
}

static void vectorCreateT4()
{
        struct Vector *vec;

        if ((vec = VectorCreate(0, 0)) == NULL)
        {
                printf("|VectorCreate(0,0)|\tVectorCreate NEGATIVE test => pass\n");
        }
        else
        {
                printf("|VectorCreate(0,0)|\tVectorCreate NEGATIVE test => fail\n");
        }

        VectorDestroy(&vec, NULL);
}

static void vectorCreateT5()
{
        struct Vector *vec;

        if ((vec = VectorCreate(-2, 0)) == NULL)
        {
                printf("|VectorCreate(-2,0)|\tVectorCreate NEGATIVE test => pass\n");
        }
        else
        {
                printf("|VectorCreate(-2,0)|\tVectorCreate NEGATIVE test => fail\n");
        }

        VectorDestroy(&vec, NULL);
}

static void vectorDestroyTest()
{
        printf("\n*********************************************************************\n"
               "*************************vector destroy test*************************\n"
               "*********************************************************************\n");
        vectorDestroyT1();
        vectorDestroyT2();
        /**add test**/
}

static void vectorDestroyT1()
{
        VectorDestroy(NULL, NULL);
        printf("|VectorDestroy(NULL, NULL)| => pass\n");
}

static void vectorDestroyT2()
{
        Vector *vec;

        vec = VectorCreate(2, 2);

        VectorDestroy(&vec, NULL);
        VectorDestroy(&vec, NULL);

        printf("|double VectorDestroy| => pass\n");
}

static void VectorAppendTest()
{
        printf("\n********************************************************************\n"
               "*************************vector append test*************************\n"
               "********************************************************************\n");
        AppendNullVec();
        AppendNullItem();
        AppendWithIncrease();
}

static void AppendNullVec()
{
        char data = 'q';

        if (VectorAppend(NULL, &data) == VECTOR_UNINITIALIZED_ERROR)
        {
                printf("VectorAppend null vector => pass\n");
                return;
        }
        printf("VectorAppend null vector => fail\n");
}

static void AppendNullItem()
{
        Vector *vec;

        vec = VectorCreate(2, 2);
        if (VectorAppend(vec, NULL) == VECTOR_ITEM_UNINITIALIZED_ERROR)
        {
                printf("VectorAppend null item => pass\n");
                VectorDestroy(&vec, NULL);
                return;
        }

        printf("VectorAppend null item => fail\n");

        VectorDestroy(&vec, NULL);
}

static void AppendWithIncrease()
{
        Vector *vec;
        char *a[3];

        vec = VectorCreate(2, 3);

        a[0] = malloc(sizeof(char));
        *a[0] = 'w';
        VectorAppend(vec, (void *)a[0]);

        a[1] = malloc(sizeof(char));
        *a[1] = 'q';
        VectorAppend(vec, (void *)a[1]);

        a[2] = malloc(sizeof(char));
        *a[2] = 'x';
        VectorAppend(vec, (void *)a[2]);

        if (VectorSize(vec) == 3)
        {
                printf("VectorAppend increase vector => pass\n");
                VectorDestroy(&vec, FreeCharElement);

                return;
        }
        printf("VectorAppend increase vector => fail\n");

        VectorDestroy(&vec, FreeCharElement);
}