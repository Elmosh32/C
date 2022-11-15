#include <stdlib.h>
#include <stdio.h>

#include "linkedList.h"

Person person1[3] = {{32,"lior",21,NULL},{31,"yakov",31,NULL},{38,"michal",46,NULL}};
Person person2[3] = {{28,"hagar",26,NULL},{25,"liran",28,NULL},{20,"yosi",36,NULL}};
Person* del;

void files(){
        FILE *cfptr;
        Person person2[5];
        if ((cfptr = fopen("clients.dat","r")) == NULL) {
                printf("file could not open\n");
        }else{
                printf("%-10s%-13s%s\n","account", "Name", "balance");
                fscaf(cfptr, "%d%s%lf", &account)

        }
}

void ageCheck(){
        int agee;
        Person* head = (Person*) malloc(sizeof(Person));
        head =NULL;
        head = ListInsertHead(head, &person1[0]);
        head = ListInsertHead(head, &person1[1]);
        head = ListInsertHead(head, &person1[2]);

        printf("%d\n",age(head));
        printf("%d\t%d\n",age2(head), age2(head)->m_age);

}
/***************************************************************
                    ListInsertHead
***************************************************************/
void insertHeadNull1(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListInsertHead(NULL,&person1[1]);
        printf("insert func - ListInsertHead(NULL,Node)\t");

        if(head == NULL)
                printf("=>\tFAIL\n");
        else
                printf("=>\tPASS\n");
}

void insertHeadNull2(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListInsertHead(&person1[1], NULL);
        printf("insert func - ListInsertHead(Node,NULL)\t");

        if(head == NULL)
                printf("=>\tFAIL\n");
        else
                printf("=>\tPASS\n");
}

void insertHeadNull3(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListInsertHead(NULL, NULL);
        printf("insert func - ListInsertHead(NULL,NULL)\t");

        if(head == NULL)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}

void insertHeadValid1(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListInsertHead(head, &person1[0]);
        printf("insert func - ListInsertHead(list,Node)\t");

        if(head != NULL)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}

void insertHeadValid2(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListInsertHead(&person1[0], head);
        printf("insert func - ListInsertHead(Node,list)\t");

        if(head != NULL)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}

/***************************************************************
                    ListInsertByKey
***************************************************************/
void InsertByKeyNull1(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListInsertByKey(&person1[0], 1, NULL);
        printf("insert func - ListInsertByKey(Node,int,NULL)\t");

        if(head != NULL)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}

void InsertByKeyNull2(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListInsertByKey(NULL, 1, &person1[0]);
        printf("insert func - ListInsertByKey(NULL,int,Node)\t");

        if(head != NULL)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}

void InsertByKeyNull3(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListInsertByKey(NULL, 1, NULL);
        printf("insert func - ListInsertByKey(NULL,int,NULL)\t");

        if(head != NULL)
                printf("=>\tFAIL\n");
        else
                printf("=>\tPASS\n");
}

void InsertByKeyValid1(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListInsertByKey(&person1[0], 1, head);
        printf("insert func - ListInsertByKey(Node,int,list)\t");

        if(head != NULL)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}

void InsertByKeyValid2(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListInsertByKey(head, 1, &person1[0]);
        printf("insert func - ListInsertByKey(list,int,Node)\t");

        if(head != NULL)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}
void InsertByKeySortCheck1(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListInsertByKey(head, 38, &person1[2]);
        head = ListInsertByKey(head, 32, &person1[0]);
        printf("insert func - ListInsertByKey sort check(1)\t");

        if(head->m_id < head->m_next->m_id)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}

void InsertByKeySortCheck2(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListInsertByKey(head, 32, &person1[0]);
        head = ListInsertByKey(head, 38, &person1[2]);
        printf("insert func - ListInsertByKey sort check(2)\t");

        if(head->m_id < head->m_next->m_id)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}

/***************************************************************
                    ListInsertByKey
***************************************************************/
void recInsertByKeyNull1(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListInsertByKeyRec(&person1[0], 1, NULL);
        printf("insert func - ListInsertByKeyRec(Node,int,NULL)\t");

        if(head != NULL)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}

void recInsertByKeyNull2(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListInsertByKeyRec(NULL, 1, &person1[0]);
        printf("insert func - ListInsertByKeyRec(NULL,int,Node)\t");

        if(head != NULL)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}

void recInsertByKeyNull3(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListInsertByKeyRec(NULL, 1, NULL);
        printf("insert func - ListInsertByKeyRec(NULL,int,NULL)\t");

        if(head != NULL)
                printf("=>\tFAIL\n");
        else
                printf("=>\tPASS\n");
}

void recInsertByKeyValid1(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListInsertByKeyRec(&person1[0], 1, head);
        printf("insert func - ListInsertByKeyRec(Node,int,list)\t");

        if(head != NULL)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}

void recInsertByKeyValid2(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListInsertByKeyRec(head, 1, &person1[0]);
        printf("insert func - ListInsertByKeyRec(list,int,Node)\t");

        if(head != NULL)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}

void recInsertByKeySortCheck1(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListInsertByKeyRec(head, 38, &person1[2]);
        head = ListInsertByKeyRec(head, 32, &person1[0]);
        printf("insert func - ListInsertByKeyRec sort check(1)\t");

        if(head->m_id < head->m_next->m_id)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}

void recInsertByKeySortCheck2(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListInsertByKeyRec(head, 32, &person1[0]);
        head = ListInsertByKeyRec(head, 38, &person1[2]);
        printf("insert func - ListInsertByKeyRec sort check(2)\t");

        if(head->m_id < head->m_next->m_id)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}
/***************************************************************
                    ListRemoveHead
***************************************************************/
void removeHeadNull1(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListRemoveHead(NULL, &del);
        printf("Delete func - ListRemoveHead(NULL,item)\t");

        if(head == NULL)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}

void removeHeadNull2(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListRemoveHead(NULL, NULL);
        printf("Delete func - ListRemoveHead(NULL,NULL)\t");

        if(head == NULL)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}

void removeHeadNull3(){
        Person* head = (Person*) malloc(sizeof(Person));
        head = ListRemoveHead(head, NULL);
        printf("Delete func - ListRemoveHead(list,NULL)\t");

        if(head == NULL)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}

void validRemove1(){
        Person* head = (struct Person*) calloc(10,sizeof(struct Person));
        head = NULL;

        head = ListInsertByKey(head, 32, &person1[0]);
        head = ListRemoveHead(head, &del);

        printf("Delete func - ListRemoveHead(list,item)\t");

        if(head == NULL)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}

void validRemove2(){
        Person* head = (Person*) malloc(sizeof(Person));

        head = ListInsertByKey(head, 32, &person1[0]);
        head = ListInsertByKey(head, 38, &person1[2]);
        head = ListInsertByKey(head, 25,&person2[1]);
        head = ListRemoveHead(head, &del);
        printf("Delete func - ListRemoveHead(list,item)\t");

        if(head != NULL)
                printf("=>\tPASS\n");
        else
                printf("=>\tFAIL\n");
}
/**
   Person* head = (Person*) malloc(sizeof(Person));
   Person** del;
   head = NULL;
   PrintList(head);

   head = ListInsertByKey(head, 32,&person1[0]);
   head = ListInsertByKey(head, 31,&person1[1]);
   head = ListInsertByKey(head, 28,&person2[0]);
   head = ListInsertByKey(head, 25,&person2[1]);
   head = ListInsertByKey(head, 20,&person2[2]);
   head = ListInsertByKeyRec(head, 38,&person1[2]);
   head = ListRemoveHead(head,del);
   head = ListRemoveByKeyRec(head,25,del);
 **/
