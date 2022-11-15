#include <stdio.h>
#include "myMalloc.h"

#define BLOCK_SIZE sizeof(long)
#define MIN_MALLOC_SIZE (3 * BLOCK_SIZE)
#define ALIGNMENT 8
#define METADATA_AT_INDEX(memory, index) (((long *)memory)[index])

static size_t CalculateBlockSize(size_t _requiredBlockSize);
static void *MetaDataInit(void *_memory, size_t _requiredBlockSize, int _index);

void MyMallocInit(void *_memory, size_t _memorySize)
{
    if (_memory == NULL || _memorySize <= MIN_MALLOC_SIZE)
    {
        return;
    }

    METADATA_AT_INDEX(_memory, 0) = (long)_memorySize;
    METADATA_AT_INDEX(_memory, 1) = (long)_memorySize - MIN_MALLOC_SIZE;
    METADATA_AT_INDEX(_memory, _memorySize - 1) = 0;
}

void *MyMalloc(void *_memory, size_t _requiredBlockSize)
{
    int index = 1;
    size_t blockSize;

    if (_memory == NULL || _requiredBlockSize <= 0)
    {
        return NULL;
    }

    blockSize = CalculateBlockSize(_requiredBlockSize);
    if (METADATA_AT_INDEX(_memory, 0) - MIN_MALLOC_SIZE <= blockSize)
    {
        return NULL;
    }

    while (METADATA_AT_INDEX(_memory, index) != 0)
    {
        if (METADATA_AT_INDEX(_memory, index) > 0)
        {
            if (METADATA_AT_INDEX(_memory, index) >= blockSize)
            {
                return MetaDataInit(_memory, blockSize, index);
            }
            index += METADATA_AT_INDEX(_memory, index + 1);
        }
        else
        {
            index += (METADATA_AT_INDEX(_memory, index) * -1) + 1;
        }
    }

    return NULL;
}

void MyFree(void *_myBlock)
{
    long *metaData, *nextMetaData, *prevMetaData;

    if (_myBlock == NULL)
    {
        return;
    }

    metaData = (long *)_myBlock;
    /* check double free*/
    if ((*metaData) > 0)
    {
        return;
    }

    nextMetaData = metaData + ((((*metaData) * (-1)) + 1));

    if (*nextMetaData > 0)
    {
        *metaData = (*metaData) * (-1) + *nextMetaData + BLOCK_SIZE;
        *nextMetaData = 0;
    }
    else
    {
        *metaData = (*metaData) * (-1);
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

static void *MetaDataInit(void *_memory, size_t _requiredBlockSize, int _index)
{
    METADATA_AT_INDEX(_memory, _index + _requiredBlockSize + 1) = METADATA_AT_INDEX(_memory, _index) - _requiredBlockSize;
    METADATA_AT_INDEX(_memory, _index) = _requiredBlockSize * -1;
    return &METADATA_AT_INDEX(_memory, _index);
}
