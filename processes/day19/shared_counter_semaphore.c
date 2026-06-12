#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>

struct shared_data
{
    int counter;
    sem_t sem;
};

int main()
{
    int shmid;
    struct shared_data *shm;
    pid_t pid;

    shmid = shmget(IPC_PRIVATE, sizeof(struct shared_data), IPC_CREAT | 0666);
    if(shmid < 0)
    {
        perror("shmget failed");
        exit(1);
    }

    shm = (struct shared_data *)shmat(shmid, NULL, 0);
    if(shm == (struct shared_data *)-1)
    {
        perror("shmat failed");
        exit(1);
    }

    shm->counter = 0;
    if(sem_init(&(shm->sem), 1, 1) < 0)
    {
        perror("sem_init failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if(pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if(pid == 0)
    {
        for(int i = 0; i < 100000; i++)
        {
            sem_wait(&(shm->sem));
            (shm->counter)++;
            sem_post(&(shm->sem));
        }
        shmdt(shm);
        exit(0);
    }
    else
    {
        for(int i = 0; i < 100000; i++)
        {
            sem_wait(&(shm->sem));
            (shm->counter)++;
            sem_post(&(shm->sem));
        }
        wait(NULL);
        printf("Final counter value is %d\n", shm->counter);
        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}