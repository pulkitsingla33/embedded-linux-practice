#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 8
#define TOTAL_ELEMENTS 10

typedef struct
{
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int count;
    sem_t mutex;
    sem_t full;
    sem_t empty;
} SharedMem;

void run_producer(SharedMem *shm)
{
    for(int i = 0; i < TOTAL_ELEMENTS; i++)
    {
        sem_wait(&(shm->empty));
        sem_wait(&(shm->mutex));
        shm->buffer[shm->tail] = i;
        shm->tail = (shm->tail + 1) % BUFFER_SIZE;
        shm->count++;
        sem_post(&(shm->mutex));
        printf("[Producer]: Produced %d at index %d\n", i, (i%BUFFER_SIZE));
        sleep(1);
        sem_post(&(shm->full));
    }
}

void run_consumer(SharedMem *shm)
{
    for(int i = 0; i < TOTAL_ELEMENTS; i++)
    {
        sem_wait(&(shm->full));
        sem_wait(&(shm->mutex));
        int consumed = shm->buffer[shm->head];
        shm->head = (shm->head + 1) % BUFFER_SIZE;
        shm->count--;
        sem_post(&(shm->mutex));
        printf("[Consumer]: Consumed %d at index %d\n", consumed, (i%BUFFER_SIZE));
        sleep(2);
        sem_post(&(shm->empty));
    }
}

int main()
{
    int shmid;
    SharedMem *shm;
    pid_t pid;

    shmid = shmget(IPC_PRIVATE, sizeof(SharedMem), IPC_CREAT | 0644);
    if(shmid < 0)
    {
        perror("shmget failed");
        exit(1);
    }

    shm = (SharedMem *)shmat(shmid, NULL, 0);
    if(shm == (SharedMem *)-1)
    {
        perror("shmat failed");
        exit(1);
    }

    shm->head = 0;
    shm->tail = 0;
    shm->count = 0;

    if(sem_init(&(shm->mutex), 1, 1) < 0)
    {
        perror("sem init failed");
        exit(EXIT_FAILURE);
    }
    if(sem_init(&(shm->empty), 1, BUFFER_SIZE) < 0)
    {
        perror("sem init failed");
        exit(EXIT_FAILURE);
    }
    if(sem_init(&(shm->full), 1, 0) < 0)
    {
        perror("sem init failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if(pid < 0)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0)
    {
        run_producer(shm);
        shmdt(shm);
        exit(EXIT_SUCCESS);
    }
    else
    {
        run_consumer(shm);

        wait(NULL);

        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}