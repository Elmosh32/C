/** imports **/
#include <stdlib.h>

#include "ADTDefs.h"
#include "vector.h"

/** Auxiliary functions **/
static void QuickRec(Vector* _vec, size_t _begin, size_t _end);
static int  partition(Vector* _vec, size_t _begin, size_t _end);

static void MergeRec(Vector* _vec, size_t _begin, size_t _end, int* _arr);
static void merge(Vector* _vec, size_t _begin, size_t _end, int _mid, int* _arr);

static void shell(Vector* _vec, int _numOfElements);

static ADTErr count(Vector* _vec, int _minVal, int _arrSize, int _numOfEl);

static void swap(Vector* _vector, int _leftIndex, int _rightIndex);
static int  isSorted (Vector* _vec, int _num);
static void shift (Vector* _vector, int _shiftPlace, int _currIndex);
static int  findMin (Vector* _vec, int _leftIndex, int _rightIndex);
static int  findMaxVal (Vector* _vec, int _leftIndex, int _rightIndex);
static int  findMinVal (Vector* _vec, int _leftIndex, int _rightIndex);

/**********************************************************************************
                                  Bubble Sort
**********************************************************************************/
ADTErr bubbleSort(Vector *_vec){
        int i, j, flag, item1, item2;
        size_t numOfElements;

        if(_vec == NULL) {
                return ERR_NOT_INITIALIZED;
        }

        getNumOfItems(_vec, &numOfElements);
        if (numOfElements <= 1) {
                return ERR_OK;
        }

        for (i = 0; i < numOfElements - 1; i++) {
                flag = 0;
                for (j = 0; j < numOfElements - i - 1; j++) {
                        getVector(_vec,j, &item1);
                        getVector(_vec,j+1, &item2);
                        if (item1 > item2) {
                                swap(_vec, j, j+1);
                                flag = 1;
                        }
                }

                if (flag == 0) {
                        break;
                }
        }
        return ERR_OK;
}


/**********************************************************************************
                                  Shake Sort
**********************************************************************************/
ADTErr shakeSort(Vector *_vec){
        int i, j, flag;
        int rightIndex, leftIndex = 0, item1, item2;
        size_t numOfElements;

        if(_vec == NULL) {
                return ERR_NOT_INITIALIZED;
        }

        getNumOfItems(_vec, &numOfElements);
        if (numOfElements <= 1) {
                return ERR_OK;
        }

        rightIndex = numOfElements - 1;

        while(leftIndex < rightIndex) {
                flag = 0;

                for (i = leftIndex; i < rightIndex; i++) {
                        getVector(_vec,i, &item1);
                        getVector(_vec,i+1, &item2);
                        if (item1 > item2) {
                                swap(_vec, i, i+1);
                                flag = 1;
                        }
                }
                if (flag == 0) {
                        break;
                }else{
                        rightIndex--;
                }

                for (j = rightIndex; j > leftIndex; j--) {
                        getVector(_vec,j, &item1);
                        getVector(_vec,j-1, &item2);
                        if (item1 < item2) {
                                swap(_vec, j, j-1);
                                flag = 1;
                        }
                }
                if (flag == 0) {
                        break;
                }else{
                        leftIndex++;
                }
        }
        return ERR_OK;
}

/**********************************************************************************
                                  Insertion Sort
**********************************************************************************/
ADTErr InsertionSort (Vector* _vec){
        int curr, right, currIndex = 1, rightIndex = 0, flag = 0;
        size_t numOfElements;

        if(_vec == NULL) {
                return ERR_NOT_INITIALIZED;
        }

        getNumOfItems(_vec, &numOfElements);
        if (numOfElements <= 1) {
                return ERR_OK;
        }

        while(currIndex < numOfElements) {
                do {
                        getVector(_vec, currIndex, &curr);
                        getVector(_vec, rightIndex, &right);
                        if (flag == 0 && right < curr) {
                                break;
                        }else if (right >= curr && rightIndex == 0) {
                                shift(_vec, rightIndex, currIndex);
                                break;
                        }else if(right > curr && rightIndex != 0 && flag == 0) {
                                flag = 1;
                        }else if (flag == 1 && right < curr) {
                                shift(_vec, rightIndex+1, currIndex);
                                break;
                        }
                        rightIndex--;
                } while(rightIndex >= 0);

                rightIndex = currIndex;
                currIndex++;
        }
        return ERR_OK;
}

/**********************************************************************************
                                  Quick Sort
**********************************************************************************/
ADTErr QuickSort (Vector* _vec){
        size_t numOfElements;

        if(_vec == NULL) {
                return ERR_NOT_INITIALIZED;
        }

        getNumOfItems(_vec,&numOfElements);

        if (numOfElements <= 1) {
                return ERR_OK;
        }

        QuickRec(_vec, 0, numOfElements -1);
        return ERR_OK;
}

static void QuickRec(Vector* _vec, size_t _begin, size_t _end){
        int pivot;

        if (_begin >= _end) {
                return;
        }

        pivot =  partition(_vec, _begin, _end);

        if (pivot > 0) {
                QuickRec(_vec, _begin, pivot - 1);
        }

        QuickRec(_vec, pivot + 1, _end);
}

static int partition(Vector* _vec, size_t _begin, size_t _end){
        int rightVal, leftVal, pivot, beginIndex = _begin;

        getVector(_vec, _begin, &pivot);
        _begin++;
        getVector(_vec, _end, &rightVal);
        getVector(_vec,  _begin, &leftVal);

        while(_begin < _end) {
                while(pivot < rightVal) {
                        _end--;
                        getVector(_vec, _end, &rightVal);
                }

                while(pivot >= leftVal && _begin < _end) {
                        _begin++;
                        getVector(_vec,  _begin, &leftVal);
                }

                if(_begin < _end) {
                        swap(_vec, _end, _begin);
                        getVector(_vec, _end, &rightVal);
                        getVector(_vec,  _begin, &leftVal);
                }
        }

        if(rightVal < pivot) {
                swap(_vec, _end, beginIndex);
        }

        return _end;
}

/**********************************************************************************
                                  Selection Sort
**********************************************************************************/
ADTErr selectionSort(Vector *_vec){
        int i, swapIndex;
        size_t numOfElements;

        if(_vec == NULL) {
                return ERR_NOT_INITIALIZED;
        }

        getNumOfItems(_vec, &numOfElements);
        if (numOfElements <= 1) {
                return ERR_OK;
        }

        for (i = 0; i < numOfElements - 1; i++) {
                swapIndex = findMin(_vec, i, numOfElements - 1);
                swap(_vec, i, swapIndex);
        }

        return ERR_OK;
}

/**********************************************************************************
                                  Shell Sort
**********************************************************************************/
ADTErr shellSort(Vector* _vec){
        size_t numOfElements;

        if(_vec == NULL) {
                return ERR_NOT_INITIALIZED;
        }

        getNumOfItems(_vec, &numOfElements);
        if(numOfElements <= 1 ) {
                return ERR_OK;
        }

        shell(_vec, numOfElements);
        return ERR_OK;
}

static void shell(Vector* _vec, int _numOfElements){
        int i, j, item1, item2;
        int gap = _numOfElements / 2;

        while(gap > 0) {
                for (i = gap; i < _numOfElements; i++) {
                        j = i;
                        while(j >= gap) {
                                getVector(_vec, j, &item1);
                                getVector(_vec, j - gap, &item2);

                                if(item1 <= item2) {
                                        swap(_vec, j, j - gap);
                                        j = j - gap;
                                }else{
                                        break;
                                }
                        }
                }
                gap /= 2;
        }
}

/**********************************************************************************
                                  Merge Sort
**********************************************************************************/
ADTErr MergeSort (Vector* _vec){
        size_t numOfElements;
        int *arr;

        if(_vec == NULL) {
                return ERR_NOT_INITIALIZED;
        }

        getNumOfItems(_vec,&numOfElements);
        if ((arr = (int*)malloc(sizeof(int) * numOfElements)) == NULL) {
                return ERR_NOT_INITIALIZED;
        }

        if (numOfElements <= 1) {
                return ERR_OK;
        }

        MergeRec(_vec, 0, numOfElements-1, arr);
        return ERR_OK;
}

static void MergeRec(Vector* _vec, size_t _begin, size_t _end, int* _arr){
        int mid;

        if (_begin >= _end) {
                return;
        }

        mid =  (_begin + _end)/2;

        MergeRec(_vec, _begin, mid, _arr);
        MergeRec(_vec, mid + 1, _end, _arr);

        merge(_vec, _begin, _end, mid, _arr);
}

static void merge(Vector* _vec, size_t _begin, size_t _end, int _mid, int* _arr){
        int item1, item2, i = _begin, j = _mid + 1, c = _begin;

        getVector(_vec, i, &item1);
        getVector(_vec, j, &item2);
        while(i <= _mid && j <= _end) {
                if(item1 > item2) {
                        _arr[c] = item2;
                        c++;
                        j++;
                        getVector(_vec, j, &item2);
                }else{
                        _arr[c] = item1;
                        c++;
                        i++;
                        getVector(_vec, i, &item1);
                }
        }

/**line 347-358 add func checkTails (without if)**/
        while(i <= _mid) {
                getVector(_vec, i, &item1);
                _arr[c] = item1;
                c++;
                i++;
        }
        while(j <= _end) {
                getVector(_vec, j, &item2);
                _arr[c] = item2;
                c++;
                j++;
        }

        for(i = _begin; i <= _end; i++) {
                setVector(_vec, i, _arr[i]);
        }
}

/**********************************************************************************
                                  Counting Sort
**********************************************************************************/
ADTErr CountingSort (Vector* _vec){
        size_t numOfElements;
        int dif, min, max;
        if(_vec == NULL) {
                return ERR_NOT_INITIALIZED;
        }
        getNumOfItems(_vec,&numOfElements);

        if (numOfElements <= 1) {
                return ERR_OK;
        }

        min = findMinVal(_vec, 0, numOfElements-1);
        max = findMaxVal(_vec, 0, numOfElements-1);
        dif = (max - min) + 1;

        if((count(_vec, min, dif, numOfElements)) ==  ERR_NOT_INITIALIZED)
                return ERR_NOT_INITIALIZED;
        return ERR_OK;
}

static ADTErr count(Vector* _vec, int _minVal, int _arrSize, int _numOfEl){
        int i, item, index;
        int *cumulativeArr, *newArr;

        if ((cumulativeArr = (int*)calloc(_arrSize, sizeof(int))) == NULL) {
                return ERR_NOT_INITIALIZED;
        }

        if ((newArr = (int*)calloc(_numOfEl, sizeof(int))) == NULL) {
                free(cumulativeArr);
                return ERR_NOT_INITIALIZED;
        }

        for (i = 0; i < _numOfEl; i++) {
                getVector(_vec, i, &item);
                cumulativeArr[item - _minVal]++;
        }

        for (i = 0; i < _arrSize; i++) {
                cumulativeArr[i + 1] += cumulativeArr[i];
        }

        for (i = _numOfEl - 1; i >= 0; i--) {
                getVector(_vec, i, &item);
                index = cumulativeArr[item]-1;
                cumulativeArr[item]--;
                newArr[index] = item;
        }

        for (i = 0; i < _numOfEl; i++) {
                setVector(_vec, i, newArr[i]);
        }

        return ERR_OK;
}

/**********************************************************************************
                             Auxiliary functions
**********************************************************************************/
static void shift (Vector* _vector, int _shiftPlace, int _currIndex){
        int insertVal, valToShift, i;
        getVector(_vector, _currIndex, &insertVal);

        for (i = _currIndex; i > _shiftPlace ; i--) {
                getVector(_vector, i - 1, &valToShift);
                setVector(_vector, i, valToShift);
        }

        setVector(_vector, _shiftPlace, insertVal);
}

static void swap(Vector* _vector, int _leftIndex, int _rightIndex){
        int biggerVal, smallerVal;

        getVector(_vector, _leftIndex, &biggerVal);
        getVector(_vector, _rightIndex, &smallerVal);

        setVector(_vector, _rightIndex, biggerVal);
        setVector(_vector, _leftIndex, smallerVal);
}

static int findMin (Vector* _vec, int _leftIndex, int _rightIndex){
        int i, min, temp, index = _leftIndex;

        getVector(_vec, _leftIndex, &min);

        for(i = _leftIndex; i <= _rightIndex ; i++) {
                getVector(_vec, i, &temp);

                if(temp < min) {
                        min = temp;
                        index = i;
                }
        }

        return index;
}

static int findMinVal (Vector* _vec, int _leftIndex, int _rightIndex){
        int i, min, temp;

        getVector(_vec, _leftIndex, &min);

        for(i = _leftIndex; i <= _rightIndex ; i++) {
                getVector(_vec, i, &temp);

                if(temp < min) {
                        min = temp;
                }
        }

        return min;
}

static int findMaxVal (Vector* _vec, int _leftIndex, int _rightIndex){
        int i, max, temp;

        getVector(_vec, _leftIndex, &max);

        for(i = _leftIndex; i <= _rightIndex ; i++) {
                getVector(_vec, i, &temp);

                if(temp > max) {
                        max = temp;
                }
        }

        return max;
}

static int isSorted (Vector* _vector, int _num){
        int i;
        int biggerVal, smallerVal;

        for (i = 0; i < _num; i++) {
                getVector(_vector, i, &smallerVal);
                getVector(_vector, i+1, &biggerVal);
                if (smallerVal > biggerVal) {
                        return 0;
                }
        }
        return 1;
}
