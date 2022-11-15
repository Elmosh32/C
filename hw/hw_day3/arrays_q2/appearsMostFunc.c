#include <stdio.h>

int appearsMost(int arr[], int _size){
        int i, j;
        int max = 0, maxCounter = 0, counter, currVal;

        for (i = 0; i < _size; i++) {
                counter = 0;
                currVal = arr[i];

                /**checks how much vals in the array equals to arr[j]**/
                for (j = i; j < _size; j++) {
                        if (arr[j] == currVal) {
                                counter++;
                        }
                }

                if (counter > maxCounter) {
                        maxCounter = counter;
                        max = currVal;
                }
        }
        return max;
}
