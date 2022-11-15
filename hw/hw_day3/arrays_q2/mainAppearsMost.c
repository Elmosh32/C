#include <stdio.h>
#include "appearsMost.h"

int main()
{
        int arr[] = {5,5,6,5,6,6,6,5,-3,-4,0,-3,5,1,5,3};
        int returnVal;
        int size = (arr, sizeof(arr)/sizeof(arr[0]));

        if(errCode == SIZE_ERROR) {
                printf("Sorry the array is to big..");
                return SIZE_ERROR;
        }

        returnVal = appearsMost(arr, size);
        printf("In the array, the number appearing most frequently is:%d\n",returnVal);

        return OK;
}
