#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define PRODUCER_DATA 5
#define MAX_PRODUCERS 5
#define MAX_CONSUMERS 1

typedef struct
{
    int data[BUFFER_SIZE];
    int head; 
    int tail;
} CircularBuffer;

CircularBuffer cb;
pthread_mutex_t mutex;
sem_t full, empty;


int enqueue(int data)
{
    cb.data[cb.tail] = data;
    printf("Writing %d at %d\n", data, cb.tail);
    cb.tail = (cb.tail + 1) % BUFFER_SIZE;
}

void dequeue()
{
    int ret_val = cb.data[cb.head];
    printf("Reading %d from %d\n", ret_val, cb.head);
    cb.head = (cb.head + 1) % BUFFER_SIZE;
}

void *producer(void *arg)
{
    for(int i = 0; i < PRODUCER_DATA; i++)
    {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        printf("[Producer %ld]: ", ((long)arg));
        enqueue(i);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(rand() % 4);
    }

    return NULL;
}

void *consumer(void *arg)
{
    for(int i = 0; i < (MAX_PRODUCERS * PRODUCER_DATA); i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        printf("[Consumer %ld]: ", ((long)arg));
        dequeue();
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(rand() % 2);
    }
}



int main()
{
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    cb.head = 0;
    cb.tail = 0;

    pthread_t producers[MAX_PRODUCERS];
    pthread_t consumers[MAX_CONSUMERS];

    for(int i = 0; i < MAX_PRODUCERS; i++)
    {
        pthread_create(&producers[i], NULL, producer, (void *)(long)i);
    }
    
    for(int i = 0; i < MAX_CONSUMERS; i++)
    {
        pthread_create(&consumers[i], NULL, consumer, (void *)(long)i);
    }

    for(int i = 0; i < MAX_PRODUCERS; i++)
    {
        pthread_join(producers[i], NULL);
    }

    for(int i = 0; i < MAX_CONSUMERS; i++)
    {
        pthread_join(consumers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}