#include <pthread.h>
#include <stdio.h>
#define NUM_OF_THREADS 10
#define PRINT_NUM 10000

int globalVar;

void *PrintFunc(void *tid)
{
    int i, localVar = 0;
    for (i = 0; i < PRINT_NUM; i++)
    {
        globalVar++;
        localVar++;
        printf("Thread ID:%d local:%d global:%d \n", *(int *)tid, localVar, globalVar);
    }
    pthread_exit(NULL);
}

int main()
{
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i;
    pthread_t threads[NUM_OF_THREADS];

    for (i = 0; i < NUM_OF_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, PrintFunc, &arr[i]);
    }

    for (i = 0; i < NUM_OF_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
