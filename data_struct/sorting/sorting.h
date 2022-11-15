#ifndef __SORT_H__
#define __SORT_H__

/**
   Description:     Bubble sort is a simple sorting algorithm that repeatedly steps through the input list element by element,
                    comparing the current element with the one after it, swapping their values ​​if needed.
                    These passes through the list are repeated until no swaps have to be performed during a pass,
                    meaning that the list has become fully sorted.
   input:           Vector *_vec
   output:          ADTErr =>
                    if _vec==NULL returns ERR_NOT_INITIALIZED else ERR_OK.
   Complexity:
   Time =>          typical case = O(n/2) * O(n-1) = O(n^2)
                    worst case = O(n/2) * O(n-1) = O(n^2)
                    best case = O(n)
   Memory =>        O(1)
   Stability =>     stable sorting algorithm.
 **/
ADTErr bubbleSort(Vector *_vec);

/**
   Description:     Shake sort is an extension of bubble sort.
                    The algorithm extends bubble sort by operating in two directions.
                    While it improves on bubble sort by more quickly moving items to the beginning of the list,
                    it provides only marginal performance improvements.
                    Expected 15 to 30 percent better performance than bubble sort.
   input:           Vector *_vec
   output:          ADTErr =>
                    if _vec==NULL returns ERR_NOT_INITIALIZED else ERR_OK.
   Complexity:
   Time =>          typical case = O(n/2) * O(n-1) = O(n^2)
                    worst case = O(n/2) * O(n-1) = O(n^2)
                    best case = O(n)
   Memory =>        O(1)
   Stability =>     stable sorting algorithm.
 **/
ADTErr shakeSort(Vector *_vec);

/**
   Description:     Insertion sort iterates, consuming one input element each repetition,
                    and grows a sorted output list. At each iteration,
                    insertion sort removes one element from the input data,
                    finds the location it belongs within the sorted list, and inserts it there.
                    It repeats until no input elements remain.
                    Expected 50% better performance than bubble sort.
   input:           Vector *_vec
   output:          ADTErr =>
                    if _vec==NULL returns ERR_NOT_INITIALIZED else ERR_OK.
   Complexity:
   Time =>          typical case =  O(n^2)
                    worst case =  O(n^2)
                    best case = O(n)
   Memory =>        O(1)
   Stability =>     stable sorting algorithm.
 **/
ADTErr InsertionSort (Vector* _vec);

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
   Stability =>     not a stable sort=>
                    the relative order of equal sort items is not preserved.
 **/
ADTErr QuickSort (Vector* _vec);

/**
   Description:     The algorithm divides the input list into two parts: a sorted sublist of items which is built up from left to right at the front (left)
                    of the list and a sublist of the remaining unsorted items that occupy the rest of the list.
                    Initially, the sorted sublist is empty and the unsorted sublist is the entire input list.
                    The algorithm proceeds by finding the smallest (or largest, depending on sorting order) element in the unsorted sublist,
                    exchanging (swapping) it with the leftmost unsorted element (putting it in sorted order), and moving the sublist boundaries one element to the right.
   input:           Vector *_vec
   output:          ADTErr =>
                    if _vec==NULL returns ERR_NOT_INITIALIZED else ERR_OK.
   Complexity:
   Time =>          typical case =  O(n^2)
                    worst case   =  O(n^2)
                    best case    =  O(n^2)
   Memory =>        O(1)
   Stability =>     not a stable sort=>
                    the relative order of equal sort items is not preserved.
 **/
ADTErr selectionSort(Vector *_vec);

/**
   Description:     The algorithm divides the input list into two parts: a sorted sublist of items which is built up from left to right at the front (left)
                    of the list and a sublist of the remaining unsorted items that occupy the rest of the list.
                    Initially, the sorted sublist is empty and the unsorted sublist is the entire input list.
                    The algorithm proceeds by finding the smallest (or largest, depending on sorting order) element in the unsorted sublist,
                    exchanging (swapping) it with the leftmost unsorted element (putting it in sorted order), and moving the sublist boundaries one element to the right.
   input:           Vector *_vec
   output:          ADTErr =>
                    if _vec==NULL returns ERR_NOT_INITIALIZED else ERR_OK.
   Complexity:
   Time =>          typical case =  O(n*Log(n))
                    worst case   =  O(n^2)
                    best case    =  O(n*Log(n))
   Memory =>        O(1)
   Stability =>     stable sorting algorithm =>
                    the order of equal elements is the same in the input and output.
 **/
ADTErr shellSort(Vector* _vec);

/**
   Description:     Conceptually, a merge sort works as follows:
                    1) Divide the unsorted list into n sublists, each containing one element (a list of one element is considered sorted).
                    2) Repeatedly merge sublists to produce new sorted sublists until there is only one sublist remaining. This will be the sorted list.
   input:           Vector *_vec
   output:          ADTErr =>
                    if _vec==NULL returns ERR_NOT_INITIALIZED else ERR_OK.
   Complexity:
   Time =>          typical case =  O(n*Log(n))
                    worst case   =  O(n*Log(n))
                    best case    =  O(n*Log(n))
   Memory =>        O(1)
   Stability =>     stable sorting algorithm =>
                    the order of equal elements is the same in the input and output.
 **/
ADTErr MergeSort (Vector* _vec);

/**
   Description:     The algorithm operates by counting the number of objects that possess distinct key values
                    and applying prefix sum on those counts to determine the positions of each key value in the output sequence.
   input:           Vector *_vec
   output:          ADTErr =>
                    if _vec==NULL returns ERR_NOT_INITIALIZED else ERR_OK.
                    if allocation of cumulativeArr OR  newArr failed returns ERR_NOT_INITIALIZED.
   Complexity:
   Time =>          typical case =  O(n)
                    worst case   =  O(n)
                    best case    =  O(n)
   Memory =>        O(n)
   Stability =>     stable sorting algorithm =>
                    the order of equal elements is the same in the input and output.
 **/
ADTErr CountingSort (Vector* _vec);

#endif /* endif __SORT_H__ */
