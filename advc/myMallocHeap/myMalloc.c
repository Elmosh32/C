#include <stdio.h>
#include <stdlib.h>
#include "myMalloc.h"
#include "../genHeap/genHeap.h"
#include "../genVec/genVector.h"

#define BLOCK_SIZE sizeof(long)
#define MIN_MALLOC_SIZE (3 * BLOCK_SIZE)

#define TRUE 1
#define ALIGNMENT 8
#define INITIALIZE_FAIL -1
#define INITIALIZE_SUCCESS 1

typedef struct myMallocStruct
{
    Heap *m_emptyBlock;
    Vector *m_mallocVec;
} myMallocStruct;

static size_t CalculateBlockSize(size_t _requiredBlockSize);
static myMallocStruct *buildMalloc(size_t _memorySize);
static int initializeMalloc(myMallocStruct *_mallocStruct, size_t _memorySize);

void MyMallocInit(void *_memory, size_t _memorySize)
{
    myMallocStruct *mallocStruct;

    if (_memory == NULL || _memorySize < MIN_MALLOC_SIZE)
    {
        return;
    }

    if (mallocStruct = (buildMalloc(_memorySize)) == NULL)
    {
        return;
    }

    if ((initializeMalloc(mallocStruct, _memorySize)) != VECTOR_SUCCESS)
    {
        return;
    }

    _memory = (void *)mallocStruct;
}

void *MyMalloc(void *_memory, size_t _requiredBlockSize)
{
    long *MetaData;
    size_t blockSize;
    size_t index;
    long *val, *nextVal, *retVal;
    if (_memory == NULL || (*(long *)_memory - MIN_MALLOC_SIZE) <= _requiredBlockSize)
    {
        printf("MIN_MALLOC_SIZE:%ld\n", _requiredBlockSize);

        return NULL;
    }

    blockSize = CalculateBlockSize(_requiredBlockSize);

    if ((index = HeapForEach(((myMallocStruct *)_memory)->m_emptyBlock, MinHeap, (void *)blockSize)) != HeapSize(((myMallocStruct *)_memory)->m_emptyBlock))
    {
        VectorGet(((myMallocStruct *)_memory)->m_mallocVec, index, (void **)&val);
        if (VectorGet(((myMallocStruct *)_memory)->m_mallocVec, index + 2, (void **)&nextVal) == VECTOR_SUCCESS)
        {
            if (*val >= blockSize && *nextVal >= 0)
            {
                VectorSet(((myMallocStruct *)_memory)->m_mallocVec, index + blockSize + 1, (void *)(*val - blockSize));
                VectorSet(((myMallocStruct *)_memory)->m_mallocVec, index, (void *)((*val - blockSize) * -1));
                VectorGet(((myMallocStruct *)_memory)->m_mallocVec, index + blockSize, (void **)&retVal);
                return &retVal;
            }
        }

        if (*val >= blockSize)
        {
            /* code */
        }

        /**
                ((int *)_memory)[i + _requiredBlockSize + 1] = ((int *)_memory)[i] - _requiredBlockSize;
                ((int *)_memory)[i] = (-1) * _requiredBlockSize;

                return &(((int *)_memory)[i + _requiredBlockSize]);
                **/
    }

    return NULL;
}

void MyFree(void *_myBlock)
{
    long *MetaData = (long *)_myBlock;
    long *NextMetaData;
    MetaData--;

    if (_myBlock == NULL)
    {
        return;
    }

    if (*MetaData >= 0)
    {
        printf("free(): double free detected\nAborted (core dumped)\n:-)\n");
        return;
    }

    NextMetaData = MetaData + 1 + (((*MetaData) * (-1)) / BLOCK_SIZE);

    if (*NextMetaData > 0)
    {
        *MetaData = (*MetaData) * (-1) + *NextMetaData + BLOCK_SIZE;
        *NextMetaData = 0;
    }
    else
    {
        *MetaData = (*MetaData) * (-1);
    }
}

static size_t CalculateBlockSize(size_t _requiredBlockSize)
{
    size_t blockSize = _requiredBlockSize;

    while (1)
    {
        if (blockSize % ALIGNMENT == 0)
        {
            return blockSize;
        }
        blockSize++;
    }
}

long MinHeap(const void *_item1, const void *_item2)
{
    return *(long *)_item1 < *(long *)_item2;
}

static myMallocStruct *buildMalloc(size_t _memorySize)
{
    myMallocStruct *mallocStruct;

    if ((mallocStruct = ((myMallocStruct *)malloc(sizeof(myMallocStruct)))) == NULL)
    {
        return NULL;
    }

    if ((mallocStruct->m_mallocVec = VectorCreate(_memorySize, _memorySize)) == NULL)
    {
        free(mallocStruct);
        return NULL;
    }

    if ((mallocStruct->m_emptyBlock = HeapBuild(mallocStruct->m_mallocVec, MinHeap)) == NULL)
    {
        free(mallocStruct->m_mallocVec);
        free(mallocStruct);
        return NULL;
    }

    return mallocStruct;
}

static int initializeMalloc(myMallocStruct *_mallocStruct, size_t _memorySize)
{
    if (VectorAppend(_mallocStruct->m_mallocVec, (void *)_memorySize) != VECTOR_SUCCESS)
    {
        return INITIALIZE_FAIL;
    }

    if (VectorAppend(_mallocStruct->m_mallocVec, (void *)(_memorySize - MIN_MALLOC_SIZE)) != VECTOR_SUCCESS)
    {
        return INITIALIZE_FAIL;
    }

    if (VectorSet(_mallocStruct->m_mallocVec, _memorySize - 1, (void *)0) != VECTOR_SUCCESS)
    {
        return INITIALIZE_FAIL;
    }

    if (HeapInsert(_mallocStruct->m_emptyBlock, (void *)1) != HEAP_SUCCESS)
    {
        return INITIALIZE_FAIL;
    }

    return INITIALIZE_SUCCESS;
}