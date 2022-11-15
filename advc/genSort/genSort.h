#ifndef __GEN_SORT_H__
#define __GEN_SORT_H__

#include <stddef.h>
#include "ADTDefs.h"

typedef int (*Criteria)(const void* _first, const void* _second);


/***************************************************************************************
   Description:   Generic function to sort objects using bubblesort.
   Input:         _data: array to sort (can contain any type).
                  _arrLength: number of items in the array.
                  _elemSize: size of the elements in the array.
                  _sortCriteria: The criterion by which we will sort.
   output:        ERR_OK: if the sorting was done successfully.
   Error:         ERR_NOT_INITIALIZED: the array or Criteria was not initialized.
                  ERR_INVALID_INPUT: _arrLength or _elemSize is 0.
                  ERR_ALLOCATION_FAILED: alocation of the temp swap variable failed.
   Complexity:
   Time =>        typical case = O(n/2) * O(n-1) = O(n^2)
                  worst case = O(n/2) * O(n-1) = O(n^2)
                  best case = O(n)
   Memory =>      O(1)
   Stability =>   stable sorting algorithm.
***************************************************************************************/
ADTErr GenSort(void* _data, size_t _arrLength, size_t _elemSize, Criteria _sortCriteria);

#endif /* endif __GEN_SORT_H__ */
