#include <stdio.h>

int arrSum(int arr[], int n);

int main() {
        int arr[] = {1,0,2,0,0,3,0,4};
        int size = sizeof(arr) / sizeof(arr[0]);

        printf("arr[] = {1,0,2,0,0,3,0,4}\t => \t arrSum = %d\n",arrSum(arr, size));

        return 0;
}

int arrSum(int arr[], int n) {
        if (n > 0)
                return arrSum(arr, n-1) + arr[n-1];
        else
                return 0;
}
