#include <stdio.h>
#include "ascendingSort.h"

int main()
{
        int arr[] = {5,5,6,5,6,6,6,5,5,1,-2,-3,1,-4,2,3,5,3,5,3,5,3};
        int size = (arr, sizeof(arr)/sizeof(arr[0]));
        int errCode = sortArray(arr, size);

        if(errCode == SIZE_ERROR) {
                printf("Sorry the array is to big..");
                return SIZE_ERROR;
        }

        printArray(&arr, size);
        putchar('\n');

        return OK;
}
