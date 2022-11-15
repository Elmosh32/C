#include <stdio.h>
#include <stdlib.h>

#define POINTER_NOT_INITIALIZE NULL
#define OK 0
#define OVERFLOW -2
#define REALLOC_FAIL -3
#define UNDERFLOW -4

struct DynamicArray {
        int *dArray;
        int dArraySize;
        int dArrayBlockSize;
        int NumOfElements;
};

struct DynamicArray * DynamicArrayCreate( int size, int blockSize);
void DynamicArrayDestroy( struct DynamicArray *DynaminArrayPtr);
int DynamicArrayInsert(struct DynamicArray * DynaminArrayPtr, int data);
int DynamicArrayDelete( struct DynamicArray *DynaminArrayPtr, int* data);
