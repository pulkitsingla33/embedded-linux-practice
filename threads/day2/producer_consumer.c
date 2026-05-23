#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 10

typedef struct
{
    int buffer [BUFFER_SIZE];
    int head;
    int tail;
}
CircularBuffer;

pthread_mutex_t lock;
CircularBuffer cb;

int cb_init(CircularBuffer *cb)
{
    if(cb == NULL)
        return -1;
    
    cb->head = 0;
    cb->tail = 0;

    return 0;
}

void *producer_function(void *arg)
{
    for(int i = 0; i < 15; i++)
    {
        pthread_mutex_lock(&lock);
        if(((cb.tail + 1) % BUFFER_SIZE) == cb.head)
        {
            pthread_mutex_unlock(&lock);
            printf("Buffer Full\n");
            i--;
            sleep(1);
            continue;
        }
        else
        {
            printf("Writing %d at index %d\n", i, cb.tail);

            cb.buffer[cb.tail] = i;
            cb.tail = (cb.tail + 1) % BUFFER_SIZE;

            pthread_mutex_unlock(&lock);
            sleep(rand() % 2);
        }
    }
}

void *consumer_function(void *arg)
{
    for(int i = 0; i < 15; i++)
    {
        pthread_mutex_lock(&lock);
        if(cb.tail == cb.head)
        {
            pthread_mutex_unlock(&lock);
            printf("Buffer Empty\n");
            i--;
            sleep(1);
            continue;
        }
        else
        {
            printf("Reading %d from index %d\n", cb.buffer[cb.head], cb.head);
            
            cb.head = (cb.head + 1) % BUFFER_SIZE;

            pthread_mutex_unlock(&lock);
            sleep(rand() % 4);
        }
    }
}

int main()
{
    pthread_t producer, consumer;

    pthread_mutex_init(&lock, NULL);
    cb_init(&cb);

    printf("Starting Producer Consumer\n");

    pthread_create(&producer, NULL, producer_function, NULL);
    pthread_create(&consumer, NULL, consumer_function, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    pthread_mutex_destroy(&lock);

    printf("Finish execution\n");

    return 0;
}