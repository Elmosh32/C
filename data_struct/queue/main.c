#include <stdio.h>

int main(){
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
