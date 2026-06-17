#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_WORKERS 2
#define QUEUE_CAPACITY 10

typedef struct
{
    int number;
} Task;

Task task_queue[QUEUE_CAPACITY];
int queue_size = 0;
int head = 0;
int tail = 0;

pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queue_cond = PTHREAD_COND_INITIALIZER;

bool shutdown = false;

void execute_task(Task task, int worker_id)
{
    int result = task.number * task.number;
    printf("[Worker %d] Squared %d to get %d\n", worker_id, task.number, result);
}

void *worker_thread(void *arg)
{
    int worker_id = *(int*)arg;
    free(arg);

    while(true)
    {
        Task task;

        while(queue_size == 0 && !shutdown)
        {
            pthread_cond_wait(&queue_cond, &queue_mutex);
        }

        if(shutdown && queue_size == 0)
        {
            pthread_mutex_unlock(&queue_mutex);
            break;
        }

        task = task_queue[head];
        head = (head + 1) % QUEUE_CAPACITY;
        queue_size--;

        pthread_mutex_unlock(&queue_mutex);

        execute_task(task, worker_id);
    }

    printf("[Worker %d] Exiting.\n", worker_id);
    return NULL;
}

void submit_task(int number)
{
    pthread_mutex_lock(&queue_mutex);

    if(queue_size >= QUEUE_CAPACITY)
    {
        printf("Queue full! Dropping task %d\n", number);
        pthread_mutex_unlock(&queue_mutex);
        return;
    }

    Task new_task = {.number = number};
    task_queue[tail] = new_task;
    tail = (tail + 1) % QUEUE_CAPACITY;
    queue_size++;

    pthread_cond_signal(&queue_cond);
    pthread_mutex_unlock(&queue_mutex);
}

int main()
{
    pthread_t workers[NUM_WORKERS];

    for(int i = 0; i < NUM_WORKERS; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&workers[i], NULL, worker_thread, id);
    }

    for(int i = 1; i <= 15; i++)
    {
        submit_task(i);
    }

    sleep(3);

    pthread_mutex_lock(&queue_mutex);
    shutdown = true;
    pthread_cond_broadcast(&queue_cond);
    pthread_mutex_unlock(&queue_mutex);

    for(int i = 0; i < NUM_WORKERS; i++)
    {
        pthread_join(workers[i], NULL);
    }

    printf("Thread pool destroyed smoothly.\n");

    return 0;
}