/***************************************************************
 * Author:      Moshe Elazar
 * Project:     My Malloc
 * Description: Malloc interface for shared object
 * Version:     V1.0
 * Date:        18/10/22
 ***************************************************************/
#ifndef __MYMALLOC_H__
#define __MYMALLOC_H__
#include <stdlib.h>

/**
 * @brief initialize memory before allocation
 * @param _memory - pointer to the allocation memory
 * @param _memorySize - memory allocation size => should be more than MIN_MALLOC_SIZE = (3 * sizeof(long)) = 24
 * @return X
 * @details if _memory == null || _memorySize <= MIN_MALLOC_SIZE(24) the func return without doing anything
 * @details After initialization only _memorySize -24 bytes are available for client usage
 */
void MyMallocInit(void *_memory, size_t _memorySize);

/**
 * @brief  allocate memory of given size
 * @param _memory - pointer to the allocation memory
 * @param _requiredBlockSize
 * @return  _requiredBlockSize
 * @details if memory == NULL || _requiredBlockSize <= 0 returns null
 * @details Every allocation returns _requiredBlockSize bytes to the client, but reserves _requiredBlockSize+8 bytes from _memory.
 */
void *MyMalloc(void *_memory, size_t _requiredBlockSize);

/**
 * @brief free allocated memory of given pointer
 * @param _memory - pointer to the allocation memory
 * @return  X
 */
void MyFree(void *_myBlock);

#endif /* __MYMALLOC_H__ */