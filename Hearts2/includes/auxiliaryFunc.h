#ifndef _AUXILIARY_H_
#define _AUXILIARY_H_
#include "vector.h"

/**
   Description:     Quicksort works by selecting a 'pivot' element from the array and partitioning the other
                    elements into two sub-arrays, according to whether they are less than or greater than the pivot.
                    The sub-arrays are then sorted recursively.
                    This can be done in place, requiring small additional amounts of memory to perform the sorting.
   input:           Vector *_vec
   output:          ADTErr =>
                    if _vec==NULL returns ERR_NOT_INITIALIZED else ERR_OK.
   Complexity:
   Time =>          typical case =  O(n*Log(n))
                    worst case =  O(n^2)
                    best case = O(n*Log(n))
   Memory =>        O(1)
 **/
void QuickRec(Vector *_vec, size_t _begin, size_t _end);

void MyItoa(int _n, char s[]);

#endif /* _AUXILIARY_H_ */
