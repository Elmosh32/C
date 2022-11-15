#include <stdio.h>
#include "evenOdd.h"

int main()
{
        int arr[] = {5,5,6,5,6,6,6,5,5,1,-2,-3,1,-4,2,3,5,3,5,3,5,3};
        int size = (arr, sizeof(arr)/sizeof(arr[0]));

        if (_size > MAX_SIZE) {
                printf("Sorry the array is to big..");
                return SIZE_ERROR;
        }

        int numOfEven = evenNums(arr,size);
        int numOfOdd = oddNums(arr,size);

        printf("\nEven numbers:%d\n", numOfEven);
        printf("odd numbers:%d\n", numOfOdd);

        return 0;
}
