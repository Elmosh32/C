#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "ADTDefs.h"
#include "stack.h"
#include "vector.h"

#define MAGIC_NUMBER 91919191
#define TRUE 1
#define FALSE 0

struct Stack
{
        Vector *m_vector;
        int m_magicNum;
};

Stack*  StackCreate (size_t _size, size_t _blockSize){
        Stack* stackPtr = NULL;

        if(_size == 0 && _blockSize == 0)
                return NULL;

        stackPtr = (Stack*)malloc(sizeof(Stack));

        if(stackPtr == NULL)
                return NULL;
        stackPtr->m_vector = VectorCreate(_size, _blockSize);
        if(stackPtr->m_vector == NULL) {
                free(stackPtr);
                return NULL;
        }

        stackPtr->m_magicNum = MAGIC_NUMBER;

        return stackPtr;
}


void    StackDestroy(Stack* _stack){
        if(_stack == NULL || _stack->m_magicNum != MAGIC_NUMBER) {
                return;
        }

        _stack->m_magicNum = 0;
        VectorDestroy(_stack->m_vector);
        free(_stack);
}

ADTErr  StackPush   (Stack* _stack, int _item){
        if(_stack == NULL)
                return ERR_NOT_INITIALIZED;

        return VectorAdd(_stack->m_vector, _item);
}

ADTErr  StackPop    (Stack* _stack, int* _item){
        if(_stack == NULL || _item == NULL)
                return ERR_NOT_INITIALIZED;

        return VectorDelete(_stack->m_vector, _item);
}

ADTErr  StackTop    (Stack* _stack, int* _item){
        size_t numOfItems;
        if(_stack == NULL || _item == NULL)
                return ERR_NOT_INITIALIZED;

        getNumOfItems(_stack->m_vector, &numOfItems);

        if(numOfItems == 0)
                return ERR_EMPTY_STACK;

        return getVector(_stack->m_vector, numOfItems-1, _item);
}

int     StackIsEmpty(Stack* _stack){
        size_t numOfItems;

        if(_stack == NULL)
                return TRUE;

        getNumOfItems(_stack->m_vector, &numOfItems);

        if(numOfItems == 0)
                return TRUE;

        return FALSE;
}

void StackPrint(Stack *_stack){
        if(_stack == NULL)
                return;

        VectorPrint(_stack->m_vector);
}
