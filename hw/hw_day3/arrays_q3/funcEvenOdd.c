#include <stdio.h>

int evenNums(int arr[], int size){
        int i, counter = 0;

        for (i = 0; i < size; i++)
                if((arr[i]%2)==0) {
                        printf("|%d| ",arr[i]);
                        counter++;
                }
        return counter;
}

int oddNums(int arr[], int size){
        int i, counter = 0;

        if (size > 100)
                return SIZE_ERROR;

        for (i = 0; i < size; i++)
                if((arr[i]%2)==1) {
                        printf("|%d| ",arr[i]);
                        counter++;
                }
        return counter;
}
