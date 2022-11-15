#include <stdio.h>
#include "ascendingSort.h"

void swap(int *first, int *second);

int sortArray(int *_arr, int _size){
        int i, j;
        int temp = 0;

        if(&_arr == NULL)
                return GARBAGE_POINTER;

        if (_size > MAX_SIZE)
                return SIZE_ERROR;

        for (i = 0; i < _size; i++)
                for (j = i+1; j < _size; j++) {
                        if(_arr[i] > _arr[j]) {
                                swap(&_arr[i],&_arr[j]);
                        }
                }
        return OK;
}

void printArray(int _arr[], int _size){
        int i;
        for (i=0; i<_size; ++i) {
                printf("|%d| ", _arr[i]);
        }
}

void swap(int *first, int *second){
        int temp = *first;
        *first = *second;
        *second = temp;
}
