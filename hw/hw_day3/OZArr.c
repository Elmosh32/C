#include <stdio.h>

int main()
{
        int arr[]={1,0,0,1,1,0,0};
        int size = sizeof(arr)/sizeof(arr[0]);
        int i, counter = 0;

        for (i = 0; i < size; i++) {
                if(arr[i] == 0) {
                        counter++;
                }
        }

        for (i = 0; i < size; i++) {
                if(i < counter)
                        arr[i] = 0;
                else
                        arr[i] = 1;
        }

        for (i = 0; i < size; i++) {
                printf("|%d| ",arr[i] );
        }

        return 0;
}
