#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX_READERS 5
#define MAX_WRITERS 1
#define BUFFER_SIZE 10

sem_t mutex, wrtSem;
int buffer[BUFFER_SIZE];
int readCount = 0;

void *writer(void *arg)
{
    sem_wait(&wrtSem);
    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = rand() % 100; // Write random data to the buffer
        printf("Writer %ld wrote: %d\n", (long)arg, buffer[i]);
        sleep(1); // Simulate time taken to write
    }
    sem_post(&wrtSem);
    
    return NULL;
}

void *reader(void *arg)
{
    sem_wait(&mutex);
    readCount++;
    if (readCount == 1) {
        sem_wait(&wrtSem); // First reader locks the writer
    }
    sem_post(&mutex);
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("Reader %ld read: %d\n", (long)arg, buffer[i]);
        sleep((rand() % 3) + 1); // Simulate time taken to read
    }
    sem_wait(&mutex);
    readCount--;
    if (readCount == 0) {
        sem_post(&wrtSem); // Last reader releases the writer
    }
    sem_post(&mutex);
    
    return NULL;
}

int main()
{
    pthread_t writerThreads[MAX_WRITERS];
    pthread_t readerThreads[MAX_READERS];

    sem_init(&mutex, 0, 1);
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

    sem_destroy(&mutex);
    sem_destroy(&wrtSem);
    return 0;
}
