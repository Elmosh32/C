#include <stdio.h>

/* import && constant */
#include <stdio.h>
#include <string.h>

#include "../genQueue/genQueue.h"

#define TRUE 1 /* boolean flag */

void FreeQueueElement(void *_element)
{
    free(_element);
}

/* QueueCreate tests*/
void createSizeZero()
{
    printf("Negative test: QueueCreate(0)\t\t\t=>");
    if (QueueCreate(0) != NULL)
    {
        printf("\tFail\n");
    }
    else
    {
        printf("\tPass\n");
    }
}

void validCreate()
{
    Queue *que;

    printf("Positive test: QueueCreate(3)\t\t\t=>");
    if ((que = QueueCreate(3)) == NULL)
    {
        printf("\tFail\n");
    }
    else
    {
        printf("\tPass\n");
    }

    QueueDestroy(&que, NULL);
}

/* QueueInsert tests*/
void nullInsert()
{
    int data1 = 100;

    printf("Negative test: QueueInsert(NULL, 3)\t\t=>");
    if (QueueInsert(NULL, &data1) == QUEUE_SUCCESS)
    {
        printf("\tFail\n");
    }
    else
    {
        printf("\tPass\n");
    }
}

void insertAfterDestroy()
{
    Queue *que;
    int data1 = 100;

    que = QueueCreate(3);
    QueueDestroy(&que, FreeQueueElement);

    printf("Negative test: QueueInsert after destroy\t=>");
    if (QueueInsert(que, &data1) == QUEUE_SUCCESS)
    {
        printf("\tFail\n");
    }
    else
    {
        printf("\tPass\n");
    }
}

void insertToFullQueue()
{
    Queue *que;
    int *data[4], i;

    for (i = 0; i < 4; i++)
    {
        data[i] = malloc(sizeof(int));
        *data[i] = i + 1;
    }

    que = QueueCreate(3);
    QueueInsert(que, data[0]);
    QueueInsert(que, data[1]);
    QueueInsert(que, data[2]);
    printf("Negative test: QueueInsert to full queue\t=>");
    if (QueueInsert(que, data[3]) == QUEUE_SUCCESS)
    {
        printf("\tFail\n");
    }
    else
    {
        printf("\tPass\n");
    }

    QueueDestroy(&que, FreeQueueElement);
}

void insertToNotEmptyQueue()
{
    Queue *que;
    int *data[4], i;

    for (i = 0; i < 4; i++)
    {
        data[i] = malloc(sizeof(int));
        *data[i] = i + 1;
    }

    que = QueueCreate(3);
    QueueInsert(que, data[0]);
    QueueInsert(que, data[1]);
    printf("Positive test: Insert to not empty queue\t=>");
    if ((QueueInsert(que, data[2])) != QUEUE_SUCCESS)
    {
        printf("\tFail\n");
    }
    else
    {
        printf("\tPass\n");
    }

    QueueDestroy(&que, FreeQueueElement);
}

void insertToEmptyQueue()
{
    Queue *que;
    int *data[1];
    data[0] = malloc(sizeof(int));
    *data[0] = 1;

    que = QueueCreate(3);
    printf("Positive test: Insert to empty queue\t\t=>");
    if (QueueInsert(que, data[0]) != QUEUE_SUCCESS)
    {
        printf("\tFail\n");
    }
    else
    {
        printf("\tPass\n");
    }

    QueueDestroy(&que, FreeQueueElement);
}

/* QueueRemove tests*/
void nullRemove()
{
    Queue *que;
    void *item = NULL;

    que = QueueCreate(0);

    printf("Negative test: QueueRemove(NULL, item)\t\t=>");
    if (QueueRemove(que, &item) == QUEUE_SUCCESS)
    {
        printf("\tFail\n");
    }
    else
    {
        printf("\tPass\n");
    }
}

void removeAfterDestroy()
{
    Queue *que;
    void *item = NULL;

    que = QueueCreate(3);
    QueueDestroy(&que, NULL);

    printf("Negative test: QueueRemove after destroy\t=>");
    if (QueueRemove(que, &item) == QUEUE_SUCCESS)
    {
        printf("\tFail\n");
    }
    else
    {
        printf("\tPass\n");
    }
}

void removeFromFullQueue()
{
    Queue *que;
    void *item = NULL;
    int *data[4], i;

    for (i = 0; i < 3; i++)
    {
        data[i] = malloc(sizeof(int));
        *data[i] = i + 1;
    }

    que = QueueCreate(3);
    QueueInsert(que, data[0]);
    QueueInsert(que, data[1]);
    QueueInsert(que, data[2]);

    printf("Positive test: QueueRemove from full queue\t=>");
    if (QueueRemove(que, &item) != QUEUE_SUCCESS)
    {
        printf("\tFail\n");
    }
    else
    {
        printf("\tPass\n");
    }
    free(*data);
    QueueDestroy(&que, FreeQueueElement);
}

void removeFromNotEmptyQueue()
{
    Queue *que;
    void *item = NULL;
    int *data[1];
    data[0] = malloc(sizeof(int));
    *data[0] = 1;

    que = QueueCreate(3);
    QueueInsert(que, data[0]);

    printf("Positive test: remove from not empty queue\t=>");
    if (QueueRemove(que, &item) != QUEUE_SUCCESS)
    {
        printf("\tFail\n");
    }
    else
    {
        printf("\tPass\n");
    }
    free(*data);
    QueueDestroy(&que, FreeQueueElement);
}

void removeFromEmptyQueue()
{
    Queue *que;
    void *item = NULL;

    que = QueueCreate(3);
    printf("Negative test: remove from empty queue\t\t=>");
    if (QueueRemove(que, &item) == QUEUE_SUCCESS)
    {
        printf("\tFail\n");
    }
    else
    {
        printf("\tPass\n");
    }
    QueueDestroy(&que, NULL);
}

/* QueueIsEmpty tests*/
void isEmptyToNull()
{
    Queue *que;

    que = QueueCreate(0);

    printf("Negative test: QueueIsEmpty(NULL)\t\t=>");
    if (QueueIsEmpty(que) == QUEUE_SUCCESS)
    {
        printf("\tFail\n");
    }
    else
    {
        printf("\tPass\n");
    }
}

void isEmptyAfterDestroy()
{
    Queue *que;

    que = QueueCreate(3);
    QueueDestroy(&que, FreeQueueElement);

    printf("Negative test: QueueIsEmpty after destroy\t=>");
    if (QueueIsEmpty(que) == QUEUE_SUCCESS)
    {
        printf("\tFail\n");
    }
    else
    {
        printf("\tPass\n");
    }
}

void EmptyCheckToNotEmptyQueue()
{
    Queue *que;

    int *data[1];
    data[0] = malloc(sizeof(int));
    *data[0] = 21;

    que = QueueCreate(3);
    QueueInsert(que, (void *)data[0]);
    printf("Positive test: QueueIsEmpty to not empty queue\t=>");
    if (QueueIsEmpty(que) != QUEUE_SUCCESS)
    {
        printf("\tFail\n");
    }
    else
    {
        printf("\tPass\n");
    }

    QueueDestroy(&que, FreeQueueElement);
}

void EmptyCheckToEmptyQueue()
{
    Queue *que;

    que = QueueCreate(3);
    printf("Positive test: QueueIsEmpty to empty queue\t=>");
    if (QueueIsEmpty(que) != TRUE)
    {
        printf("\tFail\n");
    }
    else
    {
        printf("\tPass\n");
    }

    QueueDestroy(&que, NULL);
}

int QueueTest()
{
    printf("\n*************************************************************\n"
           "                     QueueCreate tests\n"
           "*************************************************************\n");
    createSizeZero();
    validCreate();

    printf("\n*************************************************************\n"
           "                     QueueInsert tests\n"
           "*************************************************************\n");
    nullInsert();
    insertAfterDestroy();
    insertToFullQueue();
    insertToNotEmptyQueue();
    insertToEmptyQueue();

    printf("\n*************************************************************\n"
           "                     QueueRemove tests\n"
           "*************************************************************\n");
    nullRemove();
    removeAfterDestroy();
    removeFromFullQueue();
    removeFromNotEmptyQueue();
    removeFromEmptyQueue();

    printf("\n*************************************************************\n"
           "                     QueueIsEmpty tests\n"
           "*************************************************************\n");
    isEmptyToNull();
    isEmptyAfterDestroy();
    EmptyCheckToNotEmptyQueue();
    EmptyCheckToEmptyQueue();
    return 0;
}
