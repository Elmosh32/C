#include <stdlib.h> /*malloc*/
#include <stdio.h>  /*printf*/
#include <string.h> /*printf*/
#include <stddef.h> /*size_t*/

#include "../genDoubleList/structs.h"
#include "../genDoubleList/genDoubleList.h"

typedef struct Person Person;

struct Person
{
        int m_id;
        char m_name[20];
        int m_age;
};

void FreeListElement(void *_element)
{
        free(_element);
}

static void CreateListT1();

static void ListDestroyT1();
static void ListDestroyT2();
static void ListDestroyT3();

static void PushHeadT1();
static void PushHeadT2();
static void PushHeadT3();
static void PushHeadT4();
static void PushHeadT5();
static void PushHeadT6();

static void PushTailT1();
static void PushTailT2();
static void PushTailT3();
static void PushTailT4();
static void PushTailT5();
static void PushTailT6();

static void PopHeadT1();
static void PopHeadT2();
static void PopHeadT3();
static void PopHeadT4();
static void PopHeadT5();

static void PopTailT1();
static void PopTailT2();
static void PopTailT3();
static void PopTailT4();
static void PopTailT5();

static void ListSizeT1();
static void ListSizeT2();
static void ListSizeT3();
static void ListSizeT4();

int ListTest()
{
        printf("\n*************************************************************\n"
               "                     createList tests\n"
               "*************************************************************\n");
        CreateListT1();

        printf("\n*************************************************************\n"
               "                     ListDestroy tests\n"
               "*************************************************************\n");
        ListDestroyT1();
        ListDestroyT2();
        ListDestroyT3();

        printf("\n*************************************************************\n"
               "                     pushHead tests\n"
               "*************************************************************\n");
        PushHeadT1();
        PushHeadT2();
        PushHeadT3();
        PushHeadT4();
        PushHeadT5();
        PushHeadT6();

        printf("\n*************************************************************\n"
               "                     pushTail tests\n"
               "*************************************************************\n");
        PushTailT1();
        PushTailT2();
        PushTailT3();
        PushTailT4();
        PushTailT5();
        PushTailT6();

        printf("\n*************************************************************\n"
               "                     popHead tests\n"
               "*************************************************************\n");
        PopHeadT1();
        PopHeadT2();
        PopHeadT3();
        PopHeadT4();
        PopHeadT5();

        printf("\n*************************************************************\n"
               "                     popTail tests\n"
               "*************************************************************\n");
        PopTailT1();
        PopTailT2();
        PopTailT3();
        PopTailT4();
        PopTailT5();

        printf("\n*************************************************************\n"
               "                     ListSize tests\n"
               "*************************************************************\n");
        ListSizeT1();
        ListSizeT2();
        ListSizeT3();
        ListSizeT4();
        return 0;
}

static void CreateListT1()
{
        List *list = ListCreate();

        if (list == NULL)
        {
                printf("(1)createList test\t=>\tFAIL\n");
        }
        else
        {
                printf("(1)createList test\t=>\tPASS\n");
        }

        ListDestroy(&list, NULL);
}

static void ListDestroyT1()
{
        ListDestroy(NULL, NULL);

        printf("(1)ListDestroy test\t=>\tPASS\n");
}

static void ListDestroyT2()
{
        List *list = ListCreate();
        ListDestroy(&list, NULL);

        printf("(2)ListDestroy test\t=>\tPASS\n");
}

static void ListDestroyT3()
{
        List *list = ListCreate();
        ListDestroy(&list, NULL);
        ListDestroy(&list, NULL);

        printf("(3)ListDestroy test\t=>\tPASS\n");
}

/* ListPushHead to null list*/
static void PushHeadT1()
{
        int num = 0;
        if (ListPushHead(NULL, &num) != LIST_UNINITIALIZED_ERROR)
        {
                printf("(1)ListPushHead test\t=>\tFAIL\n");
        }
        else
        {
                printf("(1)ListPushHead test\t=>\tPASS\n");
        }
}

/** valid test insert int**/
static void PushHeadT2()
{
        List *list = ListCreate();
        int num = 5;

        if (ListPushHead(list, &num) != LIST_SUCCESS)
        {
                printf("(2)ListPushHead test\t=>\tFAIL\n");
        }
        else
        {
                printf("(2)ListPushHead test\t=>\tPASS\n");
        }

        ListDestroy(&list, NULL);
}

/** valid test list of persons**/
static void PushHeadT3()
{
        List *list = ListCreate();
        Person person1 = {2210, "itzhak", 31};
        Person person2 = {3132, "israel", 21};
        Person person3 = {1811, "michel", 46};
        Person person4 = {5112, "gal", 21};
        ListPushHead(list, &person1);
        ListPushHead(list, &person2);
        ListPushHead(list, &person3);

        if (ListPushHead(list, &person4) != LIST_SUCCESS)
        {
                printf("(3)ListPushHead test\t=>\tFAIL\n");
        }
        else
        {
                printf("(3)ListPushHead test\t=>\tPASS\n");
        }

        ListDestroy(&list, NULL);
}

/** valid test list of strings**/
static void PushHeadT4()
{
        List *list = ListCreate();
        char data1[] = "random";
        char data2[] = "something";
        char data3[] = "test";

        ListPushHead(list, &data1);
        ListPushHead(list, &data2);

        if (ListPushHead(list, &data3) != LIST_SUCCESS)
        {
                printf("(4)ListPushHead test\t=>\tFAIL\n");
        }
        else
        {
                printf("(4)ListPushHead test\t=>\tPASS\n");
        }
        ListDestroy(&list, NULL);
}

/** valid test list of strings**/
static void PushHeadT5()
{
        List *list = ListCreate();
        char data = 'a';
        char data2 = 'q';
        char data3 = 'E';

        ListPushHead(list, &data);
        ListPushHead(list, &data2);

        if (ListPushHead(list, &data3) != LIST_SUCCESS)
        {
                printf("(5)ListPushHead test\t=>\tFAIL\n");
        }
        else
        {
                printf("(5)ListPushHead test\t=>\tPASS\n");
        }
        ListDestroy(&list, NULL);
}

/** valid test double insert same val**/
static void PushHeadT6()
{
        List *list = ListCreate();
        int num = 5;

        ListPushHead(list, &num);
        ListPushHead(list, &num);
        if (ListPushHead(list, &num) != LIST_SUCCESS)
        {
                printf("(6)ListPushHead test\t=>\tFAIL\n");
        }
        else
        {
                printf("(6)ListPushHead test\t=>\tPASS\n");
        }
        ListDestroy(&list, NULL);
}

/* ListPushTail to null list*/
static void PushTailT1()
{
        int num = 0;
        if (ListPushTail(NULL, &num) != LIST_UNINITIALIZED_ERROR)
        {
                printf("(1)ListPushTail test\t=>\tFAIL\n");
        }
        else
        {
                printf("(1)ListPushTail test\t=>\tPASS\n");
        }
}

/** valid test insert int**/
static void PushTailT2()
{
        List *list = ListCreate();
        int num = 5;

        if (ListPushTail(list, &num) != LIST_SUCCESS)
        {
                printf("(2)ListPushTail test\t=>\tFAIL\n");
        }
        else
        {
                printf("(2)ListPushTail test\t=>\tPASS\n");
        }

        ListDestroy(&list, NULL);
}

/** valid test list of persons**/
static void PushTailT3()
{
        List *list = ListCreate();
        Person person1 = {2210, "itzhak", 31};
        Person person2 = {3132, "israel", 21};
        Person person3 = {1811, "michel", 46};
        Person person4 = {5112, "gal", 21};
        ListPushTail(list, &person1);
        ListPushTail(list, &person2);
        ListPushTail(list, &person3);

        if (ListPushTail(list, &person4) != LIST_SUCCESS)
        {
                printf("(3)ListPushTail test\t=>\tFAIL\n");
        }
        else
        {
                printf("(3)ListPushTail test\t=>\tPASS\n");
        }

        ListDestroy(&list, NULL);
}

/** valid test list of strings**/
static void PushTailT4()
{
        List *list = ListCreate();
        char data1[] = "random";
        char data2[] = "something";
        char data3[] = "test";

        ListPushTail(list, &data1);
        ListPushTail(list, &data2);

        if (ListPushTail(list, &data3) != LIST_SUCCESS)
        {
                printf("(4)ListPushTail test\t=>\tFAIL\n");
        }
        else
        {
                printf("(4)ListPushTail test\t=>\tPASS\n");
        }
        ListDestroy(&list, NULL);
}

/** valid test list of strings**/
static void PushTailT5()
{
        List *list = ListCreate();
        char data = 'a';
        char data2 = 'q';
        char data3 = 'E';

        ListPushTail(list, &data);
        ListPushTail(list, &data2);

        if (ListPushTail(list, &data3) != LIST_SUCCESS)
        {
                printf("(5)ListPushTail test\t=>\tFAIL\n");
        }
        else
        {
                printf("(5)ListPushTail test\t=>\tPASS\n");
        }
        ListDestroy(&list, NULL);
}

/** valid test double insert same val**/
static void PushTailT6()
{
        List *list = ListCreate();
        int num = 5;

        ListPushTail(list, &num);
        ListPushTail(list, &num);
        if (ListPushTail(list, &num) != LIST_SUCCESS)
        {
                printf("(6)ListPushTail test\t=>\tFAIL\n");
        }
        else
        {
                printf("(6)ListPushTail test\t=>\tPASS\n");
        }
        ListDestroy(&list, NULL);
}

/*negative test popHead to null*/
static void PopHeadT1()
{
        int *del;
        if (ListPopHead(NULL, (void **)&del) != LIST_UNINITIALIZED_ERROR)
        {
                printf("(1)ListPopHead test\t=>\tFAIL\n");
        }
        else
        {
                printf("(1)ListPopHead test\t=>\tPASS\n");
        }
}

/*positive test popHead to once to int val*/
static void PopHeadT2()
{
        List *list = ListCreate();
        int *del;
        int num1 = -1;
        int num2 = 2;
        int num3 = 555;

        ListPushHead(list, &num1);
        ListPushHead(list, &num2);
        ListPushHead(list, &num3);

        if (ListPopHead(list, (void **)&del) != LIST_SUCCESS || *(del) != 555)
        {
                printf("(2)ListPopHead test\t=>\tFAIL\n");
        }
        else
        {
                printf("(2)ListPopHead test\t=>\tPASS\n");
        }

        ListDestroy(&list, NULL);
}

/*positive test popHead n-times*/
static void PopHeadT3()
{
        List *list = ListCreate();
        int *del;
        int num1 = -1;
        int num2 = 2;
        int num3 = 555;

        ListPushHead(list, &num1);
        ListPushHead(list, &num2);
        ListPushHead(list, &num3);
        ListPopHead(list, (void **)&del);
        ListPopHead(list, (void **)&del);

        if (ListPopHead(list, (void **)&del) != LIST_SUCCESS || *(del) != -1)
        {
                printf("(3)ListPopHead test\t=>\tFAIL\n");
        }
        else
        {
                printf("(3)ListPopHead test\t=>\tPASS\n");
        }

        ListDestroy(&list, NULL);
}

/*negative test popHead more then n-times*/
static void PopHeadT4()
{
        List *list = ListCreate();
        int *del;
        int num1 = -1;
        int num2 = 2;
        int num3 = 555;

        ListPushHead(list, &num1);
        ListPushHead(list, &num2);
        ListPushHead(list, &num3);
        ListPopHead(list, (void **)&del);
        ListPopHead(list, (void **)&del);
        ListPopHead(list, (void **)&del);

        if (ListPopHead(list, (void **)&del) != LIST_UNDERFLOW_ERROR)
        {
                printf("(4)ListPopHead test\t=>\tFAIL\n");
        }
        else
        {
                printf("(4)ListPopHead test\t=>\tPASS\n");
        }

        ListDestroy(&list, NULL);
}

/*popHead to list with strings*/
static void PopHeadT5()
{
        List *list = ListCreate();
        char *del;
        char data1[] = "random";
        char data2[] = "something";
        char data3[] = "test";

        ListPushHead(list, &data1);
        ListPushHead(list, &data2);
        ListPushHead(list, &data3);

        ListPopHead(list, (void **)&del);
        ListPopHead(list, (void **)&del);
        if (ListPopHead(list, (void **)&del) != LIST_SUCCESS || strcmp((char *)del, "random") != 0)
        {
                printf("(5)ListPopHead test\t=>\tFAIL\n");
        }
        else
        {
                printf("(5)ListPopHead test\t=>\tPASS\n");
        }

        ListDestroy(&list, NULL);
}

/*negative test popTail to null*/
static void PopTailT1()
{
        int del;
        if (ListPopTail(NULL, (void **)&del) == LIST_SUCCESS)
        {
                printf("(1)ListPopTail test\t=>\tFAIL\n");
        }
        else
        {
                printf("(1)ListPopTail test\t=>\tPASS\n");
        }
}

/*positive test popTail to once to int val*/
static void PopTailT2()
{
        List *list = ListCreate();
        int *del;
        int num1 = -1;
        int num2 = 2;
        int num3 = 555;

        ListPushHead(list, &num1);
        ListPushHead(list, &num2);
        ListPushHead(list, &num3);

        if (ListPopTail(list, (void **)&del) != LIST_SUCCESS || *(del) != -1)
        {
                printf("(2)ListPopTail test\t=>\tFAIL\n");
        }
        else
        {
                printf("(2)ListPopTail test\t=>\tPASS\n");
        }

        ListDestroy(&list, NULL);
}

/*positive test popTail n-times*/
static void PopTailT3()
{
        List *list = ListCreate();
        int *del;
        int num1 = -1;
        int num2 = 2;
        int num3 = 555;

        ListPushHead(list, &num1);
        ListPushHead(list, &num2);
        ListPushHead(list, &num3);
        ListPopTail(list, (void **)&del);
        ListPopTail(list, (void **)&del);

        if (ListPopTail(list, (void **)&del) != LIST_SUCCESS || *(del) != 555)
        {
                printf("(3)ListPopTail test\t=>\tFAIL\n");
        }
        else
        {
                printf("(3)ListPopTail test\t=>\tPASS\n");
        }

        ListDestroy(&list, NULL);
}

/*negative test popTail more then n-times*/
static void PopTailT4()
{
        List *list = ListCreate();
        int *del;
        int num1 = -1;
        int num2 = 2;
        int num3 = 555;

        ListPushHead(list, &num1);
        ListPushHead(list, &num2);
        ListPushHead(list, &num3);
        ListPopTail(list, (void **)&del);
        ListPopTail(list, (void **)&del);
        ListPopTail(list, (void **)&del);

        if (ListPopTail(list, (void **)&del) != LIST_UNDERFLOW_ERROR)
        {
                printf("(4)ListPopTail test\t=>\tFAIL\n");
        }
        else
        {
                printf("(4)ListPopTail test\t=>\tPASS\n");
        }

        ListDestroy(&list, NULL);
}

/*ListPopTail to list with strings*/
static void PopTailT5()
{
        List *list = ListCreate();
        char *del;
        char data1[] = "random";
        char data2[] = "something";
        char data3[] = "test";

        ListPushHead(list, &data1);
        ListPushHead(list, &data2);
        ListPushHead(list, &data3);

        ListPopTail(list, (void **)&del);
        ListPopTail(list, (void **)&del);
        if (ListPopTail(list, (void **)&del) != LIST_SUCCESS || strcmp((char *)del, "test") != 0)
        {
                printf("(5)ListPopHead test\t=>\tFAIL\n");
        }
        else
        {
                printf("(5)ListPopHead test\t=>\tPASS\n");
        }

        ListDestroy(&list, NULL);
}

/*Negative test null ListSize*/
static void ListSizeT1()
{
        if (ListSize(NULL) != 0)
        {
                printf("(1)ListSize test\t=>\tFAIL\n");
        }
        else
        {
                printf("(1)ListSize test\t=>\tPASS\n");
        }
}

/*Negative test ListSize empty list*/
static void ListSizeT2()
{
        List *list = ListCreate();

        if (ListSize(list) != 0)
        {
                printf("(2)ListSize test\t=>\tFAIL\n");
        }
        else
        {
                printf("(2)ListSize test\t=>\tPASS\n");
        }

        ListDestroy(&list, NULL);
}

/*Positive test ListSize after insert*/
static void ListSizeT3()
{
        List *list = ListCreate();
        int *data[3], i;
        for (i = 0; i < 3; i++)
        {
                data[i] = malloc(sizeof(int));
        }
        *data[0] = 32;
        *data[1] = 1;
        *data[2] = 61;

        ListPushHead(list, (void *)data[0]);
        ListPushHead(list, (void *)data[1]);
        ListPushHead(list, (void *)data[2]);

        if (ListSize(list) != 3)
        {
                printf("(3)ListSize test\t=>\tFAIL\n");
        }
        else
        {
                printf("(3)ListSize test\t=>\tPASS\n");
        }

        ListDestroy(&list, FreeListElement);
}

/*Positive test ListSize after insert*/
static void ListSizeT4()
{
        List *list = ListCreate();
        int del;
        int *data[3], i;
        for (i = 0; i < 3; i++)
        {
                data[i] = malloc(sizeof(int));
        }
        *data[0] = 32;
        *data[1] = 1;
        *data[2] = 61;

        ListPushHead(list, (void *)data[0]);
        ListPushHead(list, (void *)data[1]);
        ListPushHead(list, (void *)data[2]);

        ListPopHead(list, (void **)&del);
        if (ListSize(list) != 2)
        {
                printf("(4)ListSize test\t=>\tFAIL\n");
        }
        else
        {
                printf("(4)ListSize test\t=>\tPASS\n");
        }

        ListDestroy(&list, FreeListElement);
}
