#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX_READERS 5
#define MAX_WRITERS 1
#define BUFFER_SIZE 20

pthread_mutex_t mutex;
sem_t wrtSem;
int buffer[BUFFER_SIZE];
int readCount = 0;

void *writer(void *arg)
{
    sem_wait(&wrtSem);
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        printf("Writer %ld wrote: %d\n", (long)arg, i);
        buffer[i] = i;
        sleep(1);
    }
    sem_post(&wrtSem);

    return NULL;
}

void *reader(void *arg)
{
    pthread_mutex_lock(&mutex);
    readCount++;
    if(readCount == 1)
    {
        sem_wait(&wrtSem);
    }
    pthread_mutex_unlock(&mutex);

    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        printf("Reader %ld read: %d\n", (long)arg, buffer[i]);
        sleep((rand() % 4) + 1);
    }

    pthread_mutex_lock(&mutex);
    readCount--;
    if(readCount == 0)
        sem_post(&wrtSem);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    pthread_t writerThreads[MAX_WRITERS];
    pthread_t readerThreads[MAX_READERS];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrtSem, 0, 1);

    for (int i = 0; i < MAX_WRITERS; i++) {
        pthread_create(&writerThreads[i], NULL, writer, (void *)(long)i);
    }

    for (int i = 0; i < MAX_READERS; i++) {
        pthread_create(&readerThreads[i], NULL, reader, (void *)(long)i);
    }

    for (int i = 0; i < MAX_WRITERS; i++) {
        pthread_join(writerThreads[i], NULL);
    }

    for (int i = 0; i < MAX_READERS; i++) {
        pthread_join(readerThreads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrtSem);
    return 0;
}