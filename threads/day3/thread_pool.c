#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 4
#define MAX_TASKS 10

int taskQueue[MAX_TASKS];
int taskCount = 0;

pthread_mutex_t queueMutex;

void *worker(void *arg)
{
    while (1) {
        pthread_mutex_lock(&queueMutex);
        if (taskCount > 0) {
            int task = taskQueue[--taskCount]; // Get a task from the queue
            pthread_mutex_unlock(&queueMutex);
            printf("Worker %ld processing task: %d\n", (long)arg, task);
            sleep(1); // Simulate time taken to process the task
        } else {
            pthread_mutex_unlock(&queueMutex);
            break; // No more tasks to process
        }
    }
    return NULL;
}

int main()
{
    pthread_t workers[MAX_THREADS];
    pthread_mutex_init(&queueMutex, NULL);

    for (int i = 0; i < MAX_TASKS; i++) {
        taskQueue[i] = i; // Add tasks to the queue
        taskCount++;
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_create(&workers[i], NULL, worker, (void *)(long)i);
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(workers[i], NULL);
    }


    pthread_mutex_destroy(&queueMutex);
    return 0;
}