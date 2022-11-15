#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define N 100
#define RUN 1

static void *Producer();
static void *Consumer();

int item;
sem_t empty;
sem_t full;
pthread_mutex_t mutex;

int main()
{
    pthread_t producer;
    pthread_t consumer;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);

    pthread_create(&producer, NULL, Producer, NULL);
    pthread_create(&consumer, NULL, Consumer, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

static void *Producer()
{
    while (RUN)
    {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        item++;
        printf("%d, ", item);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

static void *Consumer()
{
    while (RUN)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item--;
        printf("%d, ", item);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}
