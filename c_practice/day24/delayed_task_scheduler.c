#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef void (*task_fptr)();

typedef struct TaskNode {
    long long target_time_ms;
    task_fptr function;
    struct TaskNode *next;
} TaskNode;

TaskNode *task_queue = NULL;

long long get_current_time_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((long long)tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void schedule_task(int delay_ms, task_fptr function)
{
    long long current_time = get_current_time_ms();

    TaskNode *new_node = (TaskNode *)malloc(sizeof(TaskNode));
    new_node->target_time_ms = current_time + delay_ms;
    new_node->function = function;
    new_node->next = NULL;

    if(task_queue == NULL || new_node->target_time_ms < task_queue->target_time_ms)
    {
        new_node->next = task_queue;
        task_queue = new_node;
    }
    else {
        TaskNode *current = task_queue;
        while(current->next != NULL && current->next->target_time_ms <= new_node->target_time_ms)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void run_event_loop()
{
    while(task_queue != NULL)
    {
        long long current_time = get_current_time_ms();

        if(current_time >=  task_queue->target_time_ms)
        {
            TaskNode *temp = task_queue;
            task_queue = task_queue->next;

            temp->function();
            free(temp);
        }
        else
        {
            long long sleep_needed_ms = task_queue->target_time_ms - current_time;
            if(sleep_needed_ms > 0)
                usleep(sleep_needed_ms * 1000);
        }
    }
}


void taskA() { printf("Executed Task A\n"); }
void taskB() { printf("Executed Task B\n"); }
void taskC() { printf("Executed Task C\n"); }

int main()
{
    printf("Scheduling Tasks...\n");

    schedule_task(1000, taskA);
    schedule_task(2000, taskB);
    schedule_task(500, taskC);

    printf("Starting Event Loop...\n");
    run_event_loop();

    printf("All tasks executed.\n");
    return 0;
}