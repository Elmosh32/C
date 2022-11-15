/* import && constant */
#include <stdio.h>
#include <string.h>

#include "ADTDefs.h"
#include "queue.h"

#define OK 0   /* boolean flag */

/* QueueCreate tests*/
void createSizeZero() {
        printf("Negetive test: QueueCreate(0)\t\t\t=>");
        if (QueueCreate(0) != NULL) {
                printf("\tFail\n");
        }else{
                printf("\tPass\n");
        }
}

void validCreate() {
        printf("Positive test: QueueCreate(3)\t\t\t=>");
        if (QueueCreate(3) == NULL) {
                printf("\tFail\n");
        }else{
                printf("\tPass\n");
        }
}

/* QueueInsert tests*/
void nullInsert() {
        struct Queue *que;

        que = QueueCreate(0);

        printf("Negetive test: QueueInsert(NULL, 3)\t\t=>");
        if (QueueInsert(que, 3) == OK) {
                printf("\tFail\n");
        }else{
                printf("\tPass\n");
        }
}

void insertAfterDestroy() {
        struct Queue *que;

        que = QueueCreate(3);
        QueueDestroy(que);

        printf("Negetive test: QueueInsert after destroy\t=>");
        if (QueueInsert(que, 3) == OK) {
                printf("\tFail\n");
        }else{
                printf("\tPass\n");
        }
}

void insertToFullQueue(){
        struct Queue *que;

        que = QueueCreate(3);
        QueueInsert(que, 1);
        QueueInsert(que, 2);
        QueueInsert(que, 3);
        printf("Negetive test: QueueInsert to full queue\t=>");
        if (QueueInsert(que, 4) == OK) {
                printf("\tFail\n");
        }else{
                printf("\tPass\n");
        }
}

void insertToNotEmptyQueue(){
        struct Queue *que;

        que = QueueCreate(3);
        QueueInsert(que, 1);
        QueueInsert(que, 2);
        printf("Positive test: Insert to not empty queue\t=>");
        if (QueueInsert(que, 3) != OK) {
                printf("\tFail\n");
        }else{
                printf("\tPass\n");
        }
}

void insertToEmptyQueue(){
        struct Queue *que;

        que = QueueCreate(3);
        printf("Positive test: Insert to empty queue\t\t=>");
        if (QueueInsert(que, 1) != OK) {
                printf("\tFail\n");
        }else{
                printf("\tPass\n");
        }
}

/* QueueRemove tests*/
void nullRemove() {
        struct Queue *que;
        int *item;

        que = QueueCreate(0);

        printf("Negetive test: QueueRemove(NULL, item)\t\t=>");
        if (QueueRemove(que, item) == OK) {
                printf("\tFail\n");
        }else{
                printf("\tPass\n");
        }
}

void removeAfterDestroy() {
        struct Queue *que;
        int *item;

        que = QueueCreate(3);
        QueueDestroy(que);

        printf("Negetive test: QueueRemove after destroy\t=>");
        if (QueueRemove(que, item) == OK) {
                printf("\tFail\n");
        }else{
                printf("\tPass\n");
        }
}

void removeFromFullQueue(){
        struct Queue *que;
        int *item;

        que = QueueCreate(3);
        QueueInsert(que, 1);
        QueueInsert(que, 2);
        QueueInsert(que, 3);
        printf("Positive test: QueueRemove from full queue\t=>");
        if (QueueRemove(que, item) != OK) {
                printf("\tFail\n");
        }else{
                printf("\tPass\n");
        }
}

void removeFromNotEmptyQueue(){
        struct Queue *que;
        int *item;

        que = QueueCreate(3);
        QueueInsert(que, 1);
        printf("Positive test: remove from not empty queue\t=>");
        if (QueueRemove(que, item) != OK) {
                printf("\tFail\n");
        }else{
                printf("\tPass\n");
        }
}

void removeFromEmptyQueue(){
        struct Queue *que;
        int *item;

        que = QueueCreate(3);
        printf("Negetive test: remove from empty queue\t\t=>");
        if (QueueRemove(que, item) == OK) {
                printf("\tFail\n");
        }else{
                printf("\tPass\n");
        }
}

/* QueueIsEmpty tests*/
void isEmptyToNull() {
        struct Queue *que;

        que = QueueCreate(0);

        printf("Negetive test: QueueIsEmpty(NULL)\t\t=>");
        if (QueueIsEmpty(que) == OK) {
                printf("\tFail\n");
        }else{
                printf("\tPass\n");
        }
}

void isEmptyAfterDestroy() {
        struct Queue *que;

        que = QueueCreate(3);
        QueueDestroy(que);

        printf("Negetive test: QueueIsEmpty after destroy\t=>");
        if (QueueIsEmpty(que) == OK) {
                printf("\tFail\n");
        }else{
                printf("\tPass\n");
        }
}

void EmptyCheckToNotEmptyQueue(){
        struct Queue *que;

        que = QueueCreate(3);
        QueueInsert(que, 1);
        printf("Positive test: QueueIsEmpty to not empty queue\t=>");
        if (QueueIsEmpty(que) != OK) {
                printf("\tFail\n");
        }else{
                printf("\tPass\n");
        }
}

void EmptyCheckToEmptyQueue(){
        struct Queue *que;

        que = QueueCreate(3);
        printf("Positive test: QueueIsEmpty to empty queue\t=>");
        if (QueueIsEmpty(que) != EMPTY_QUEUE) {
                printf("\tFail\n");
        }else{
                printf("\tPass\n");
        }
}
