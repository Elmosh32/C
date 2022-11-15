#include <stdio.h>

int arrMaxVal(int arr[], int n);

int main() {
        int arr[] = {1,0,2,0,9,0,3,0,4};
        int size = sizeof(arr) / sizeof(arr[0]);

        printf("arr[] = {1,0,2,0,9,0,3,0,4}\t => \t arrMaxVal = %d\n",arrMaxVal(arr, size));

        return 0;
}

int arrMaxVal(int arr[], int n) {
        int tempMax;

        if (n==1)
                return arr[0];

        tempMax = arrMaxVal (arr, n-1);

        if (arr[n-1] > tempMax)
                return arr[n-1];
        else
                return tempMax;

}
