#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int shmid;
    int *counter;
    pid_t pid;

    shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if(shmid < 0)
    {
        perror("shmget failed");
        exit(1);
    }

    counter = (int *)shmat(shmid, NULL, 0);
    if(counter == (int *)-1)
    {
        perror("shmat failed");
        exit(1);
    }

    *counter = 0;

    pid = fork();
    if(pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if(pid == 0)
    {
        (*counter)++;
        shmdt(counter);
        exit(0);
    }
    else
    {
        wait(NULL);
        printf("Final counter value is %d\n", *counter);
        shmdt(counter);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}