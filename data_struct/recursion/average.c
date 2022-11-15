#include <stdio.h>

float arrAvg(float arr[], int n);

int main() {
        float arr[] = {0,2,1,3,8,5,9,7,4,6,10};
        int size = sizeof(arr) / sizeof(arr[0]);

        printf("arr[] = {0,2,1,3,8,5,9,7,4,6,10}\t => \t arrAvg = %f\n",arrAvg(arr, size));

        return 0;
}

float arrAvg(float arr[], int n) {
        float num;
        if (n == 1) {
                return arr[n-1];
        }else{
                num = (((arrAvg(arr, n-1)*(n-1)) + arr[n-1]));
                return (num/n);
        }
}
