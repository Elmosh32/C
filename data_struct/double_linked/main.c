#include <stdlib.h>             /*malloc*/
#include <stdio.h>             /*printf*/
#include <stddef.h>  /*size_t*/

#include "dLinkedList.h"
#include "ADTDefs.h"

void createListT1(){
        List *list = ListCreate();

        if(list == NULL)
                printf("createList test\t=>\tFAIL\n");
        else
                printf("createList test\t=>\tPASS\n");
        ListDestroy(list);

}

void pushHeadT1(){
        List *list = ListCreate();

        if(ListPushHead(list,5) != ERR_OK)
                printf("ListPushHead test\t=>\tFAIL\n");
        else
                printf("ListPushHead test\t=>\tPASS\n");
        ListDestroy(list);
}

void pushHeadT2(){
        List *list = ListCreate();

        ListPushHead(list,5);
        ListPushHead(list,5);
        if(ListPushHead(list,5) != ERR_OK)
                printf("ListPushHead test\t=>\tFAIL\n");
        else
                printf("ListPushHead test\t=>\tPASS\n");
        ListDestroy(list);
}

void pushHeadT3(){
        List *list = ListCreate();

        if(ListPushHead(list,-1) != ERR_OK)
                printf("ListPushHead test\t=>\tFAIL\n");
        else
                printf("ListPushHead test\t=>\tPASS\n");
        ListDestroy(list);
}

void pushHeadT4(){
        List *list = ListCreate();

        if(ListPushHead(list,0) != ERR_OK)
                printf("ListPushHead test\t=>\tFAIL\n");
        else
                printf("ListPushHead test\t=>\tPASS\n");
        ListDestroy(list);
}

void pushHeadT6(){
        if(ListPushHead(NULL,0) == ERR_OK)
                printf("ListPushHead test\t=>\tFAIL\n");
        else
                printf("ListPushHead test\t=>\tPASS\n");
}

void popHeadT1(){
        List *list = ListCreate();
        int del;
        ListPushHead(list,-1);
        ListPushHead(list,2);
        ListPushHead(list,555);

        if(ListPopHead(list,&del) != ERR_OK)
                printf("ListPopHead test\t=>\tFAIL\n");
        else
                printf("ListPopHead test\t=>\tPASS\n");
        ListDestroy(list);
}

void popHeadT2(){
        List *list = ListCreate();
        int del;
        ListPushHead(list,-1);
        ListPushHead(list,2);
        ListPushHead(list,555);
        ListPopHead(list,&del);
        ListPopHead(list,&del);

        if(ListPopHead(list,&del) != ERR_OK)
                printf("ListPopHead test\t=>\tFAIL\n");
        else
                printf("ListPopHead test\t=>\tPASS\n");

        ListDestroy(list);
}

void popHeadT3(){
        List *list = ListCreate();
        int del;
        ListPushHead(list,-1);
        ListPushHead(list,2);
        ListPushHead(list,555);
        ListPopHead(list,&del);
        ListPopHead(list,&del);
        ListPopHead(list,&del);

        if(ListPopHead(list,&del) == ERR_OK)
                printf("ListPopHead test\t=>\tFAIL\n");
        else
                printf("ListPopHead test\t=>\tPASS\n");

        ListDestroy(list);
}

void popHeadT4(){
        int del;
        if(ListPopHead(NULL,&del) != ERR_NOT_INITIALIZED)
                printf("ListPopHead test\t=>\tFAIL\n");
        else
                printf("ListPopHead test\t=>\tPASS\n");
}

void popTailT1(){
        List *list = ListCreate();
        int del;
        ListPushHead(list,-1);
        ListPushHead(list,2);
        ListPushHead(list,555);

        if(ListPopHead(list,&del) != ERR_OK)
                printf("ListPopTail test\t=>\tFAIL\n");
        else
                printf("ListPopTail test\t=>\tPASS\n");
        ListDestroy(list);
}

void popTailT2(){
        List *list = ListCreate();
        int del;
        ListPushHead(list,-1);
        ListPushHead(list,2);
        ListPushHead(list,555);
        ListPopTail(list,&del);
        ListPopTail(list,&del);

        if(ListPopTail(list,&del) != ERR_OK)
                printf("ListPopTail test\t=>\tFAIL\n");
        else
                printf("ListPopTail test\t=>\tPASS\n");

        ListDestroy(list);
}

void popTailT3(){
        List *list = ListCreate();
        int del;
        ListPushHead(list,-1);
        ListPushHead(list,2);
        ListPushHead(list,555);
        ListPopTail(list,&del);
        ListPopTail(list,&del);
        ListPopTail(list,&del);

        if(ListPopTail(list,&del) != ERR_UNDERFLOW)
                printf("ListPopTail test\t=>\tFAIL\n");
        else
                printf("ListPopTail test\t=>\tPASS\n");

        ListDestroy(list);
}

void popTailT4(){
        int del;
        if(ListPopTail(NULL,&del) == ERR_OK)
                printf("ListPopTail test\t=>\tFAIL\n");
        else
                printf("ListPopTail test\t=>\tPASS\n");
}

int main()
{
        printf("\n*************************************************************\n"
               "                     createList tests\n"
               "*************************************************************\n");
        createListT1();
        createListT2();
        createListAfterDestroy();

        printf("\n*************************************************************\n"
               "                     pushHead tests\n"
               "*************************************************************\n");
        pushHeadT1();
        pushHeadT2();
        pushHeadT3();
        pushHeadT4();
        pushHeadT5();
        pushHeadT6();

        printf("\n*************************************************************\n"
               "                     popHead tests\n"
               "*************************************************************\n");
        popHeadT1();
        popHeadT2();
        popHeadT3();
        popHeadT4();

        printf("\n*************************************************************\n"
               "                     popTail tests\n"
               "*************************************************************\n");
        popTailT1();
        popTailT2();
        popTailT3();
        return 0;
}
