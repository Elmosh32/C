#include  "bubble2.h"
#include <stdio.h>

#include <stdio.h>
#include <time.h>

 #define swap(x, y, t) \
        { \
                t temp; \
                temp = *x; \
                *x = *y; \
                *y = temp; \
        }

void Swap(int* xp, int* yp)
{
        int temp = *xp;
        *xp = *yp;
        *yp = temp;
}

void bubbleSort(int arr[], int n)
{
        register int i, j;
        for (i = 0; i < n - 1; i++)

                for (j = 0; j < n - i - 1; j++)
                        if (arr[j] > arr[j + 1])
                                swap(&arr[j], &arr[j + 1], int);
}

int main()
{
        int i;
        int arr[50000];
        int n;
        clock_t start_t, end_t;
        double total_t;

        start_t = clock();

        for (i = 0; i < 50000; i++) {
                arr[i] = rand() % 60000;
        }

        n = sizeof(arr) / sizeof(arr[0]);
        bubbleSort(arr, n);

        end_t = clock();

        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Total time: %f\n", total_t);

        return 0;
}
