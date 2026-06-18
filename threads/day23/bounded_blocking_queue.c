#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    int *data;
    int capacity;
    int head;
    int tail;
    int size;

    pthread_mutex_t lock;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
} BoundedQueue;

BoundedQueue *queue_init(int capacity)
{
    BoundedQueue *q = (BoundedQueue *)malloc(sizeof(BoundedQueue));
    if(!q) return NULL;

    q->data = (int *)malloc(sizeof(int) * capacity);
    q->capacity = capacity;
    q->head= 0;
    q->tail = 0;
    q->size = 0;

    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->not_full, NULL);
    pthread_cond_init(&q->not_empty, NULL);

    return q;
}

void enqueue(BoundedQueue *q, int val)
{
    pthread_mutex_lock(&q->lock);

    if(q->size == q->capacity)
    {
        pthread_cond_wait(&q->not_full, &q->lock);
    }

    q->data[q->tail] = val;
    q->tail = (q->tail + 1) % q->capacity;
    q->size++;

    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->lock);
}

int dequeue(BoundedQueue *q)
{
    pthread_mutex_lock(&q->lock);

    if(q->size == 0)
        pthread_cond_wait(&q->not_empty, &q->lock);

    int val = q->data[q->head];
    q->head = (q->head + 1) % q->capacity;
    q->size--;

    pthread_cond_signal(&q->not_full);

    pthread_mutex_unlock(&q->lock);

    return val;
}

void queue_free(BoundedQueue *q)
{
    if (!q) return;
    free(q->data);
    pthread_mutex_destroy(&q->lock);
    pthread_cond_destroy(&q->not_full);
    pthread_cond_destroy(&q->not_empty);
    free(q);
}

