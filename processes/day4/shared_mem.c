#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define ARRAY_SIZE 5

int main()
{
    int shmid;
    key_t key;
    int *shared_array;
    pid_t pid;

    key = ftok(".", 'x');
    if (key == -1)
    {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    size_t shm_size = ARRAY_SIZE * sizeof(int);
    shmid = shmget(key, shm_size, IPC_CREAT | 0666);
    if (shmid < 0)
    {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if(pid > 0)
    {
        shared_array = (int *)shmat(shmid, NULL, 0);
        if (shared_array == (int *)-1)
        {
            perror("shmat failed");
            exit(EXIT_FAILURE);
        }

        printf("Parent process writing to shared memory...\n");
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            shared_array[i] = i + 1;
        }

        shmdt(shared_array);
        wait(NULL);

        shmctl(shmid, IPC_RMID, NULL);
        printf("Parent process cleaned up shared memory.\n");
    }
    else
    {
        sleep(1); // Ensure parent writes to shared memory first
        shared_array = (int *)shmat(shmid, NULL, 0);
        if (shared_array == (void *)-1)
        {
            perror("shmat failed");
            exit(EXIT_FAILURE);
        }

        printf("Child process reading from shared memory...\n");
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            printf("shared_array[%d] = %d\n", i, shared_array[i]);
        }

        shmdt(shared_array);
        exit(0);

    }

    return 0;

}

