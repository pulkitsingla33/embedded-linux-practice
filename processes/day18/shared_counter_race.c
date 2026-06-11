#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

struct shared_data {
    int counter;
    pthread_mutex_t mutex;
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

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&(shm->mutex), &attr);
    pthread_mutexattr_destroy(&attr);

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
            pthread_mutex_lock(&(shm->mutex));
            shm->counter++;
            pthread_mutex_unlock(&(shm->mutex));
        }
        shmdt(shm);
        exit(0);
    }
    else
    {
        for(int i = 0; i < 100000; i++)
        {
            pthread_mutex_lock(&(shm->mutex));
            shm->counter++;
            pthread_mutex_unlock(&(shm->mutex));
        }
        wait(NULL);
        printf("Final counter value is %d\n", shm->counter);
        pthread_mutex_destroy(&(shm->mutex));
        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}