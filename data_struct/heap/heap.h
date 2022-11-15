#ifndef _HEAP_H_
#define _HEAP_H_

#include "vector.h"
#include "ADTDefs.h"

typedef struct Heap Heap;

/*
   Description:     The function gets vector of integers, makes malloc to the heap structure and sorts the heap.
   Input:           _vec - Pointer to the vector.
   Output:          NULL - if or if the memory allocation failed.
                    heap - Pointer to the heap structure.
   Errors:          NA
   TimeComplexity:  O(n)
 */
Heap*   HeapBuild(Vector* _vec);

/*
   Description:     The function free the heap structure.
   Input:           _heap - Pointer to the heap structure.
   Output:          NA
   Errors:          NA
   TimeComplexity:  O(1)
 */
void    HeapDestroy(Heap* _heap);

/*
   Description:     The function insert new item to the vector and sorts the heap.
   Input:           _heap - Pointer to the heap structure.
   Output:          ADTErr =>
   Errors:          ERR_NOT_INITIALIZED - if _heap == NULL OR the heap already destroyed.
                    err - if the insertion fails, returns the error type that VectorAdd function returns.
                    ERR_OK - if the insertion was done successfully
   TimeComplexity:  O(log n)
 */
ADTErr  HeapInsert(Heap* _heap, int _data);

/*
   Description:     Inserts to _data the max number (first node)
   Input:           _heap - Pointer to the heap structure.
                    _data - Pointer to get the max number.
   Output:          ADTErr =>
   Errors:          ERR_NOT_INITIALIZED - if _heap OR _data == NULL OR the heap already destroyed
                    ERR_UNDERFLOW - if the heap is empty
                    ERR_OK - success.
   TimeComplexity:  O(1)
 */
ADTErr  HeapMax(Heap* _heap, int* _data);

/*
   Description:      Inserts to _data the max number (first node) and then deletes it, moves the
                    last node to the first place and then sorts the heap.
   Input:           _heap - Pointer to the heap structure.
                    _data - Pointer to get the max number in the heap.
   Output:          ADTErr=>
   Errors:          ERR_NOT_INITIALIZED - if _heap OR _data == NULL OR the heap already destroyed.
                    ERR_UNDERFLOW - if the heap is empty
                    ERR_OK - all done normaly - success.
   TimeComplexity:  O(log n)
 */
ADTErr  HeapExtractMax(Heap* _heap, int* _data);

/*
   Description:      returns the number of elements.
   Input:           _heap - Pointer to the heap structure.
   Output:          ADTErr=>
   Errors:          ERR_NOT_INITIALIZED - if _heap OR _data == NULL OR the heap already destroyed.
                    m_heapSize - the number of elements
   TimeComplexity:  O(1)
 */
size_t     HeapItemsNum(Heap* _heap);

void HeapPrint(Heap* _heap);

#endif /*_HEAP_H_*/
