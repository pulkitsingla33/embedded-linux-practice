#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    printf("Hello World Main!\n");

    int child_status;

    if(fork())
    {
        printf("Inside Parent process\n");
        printf("PID: %d and PPID: %d\n", getpid(), getppid());

        printf("waiting for child to exit\n");
        wait(&child_status);
        printf("Child Exit Status: %d\n", WIFEXITED(child_status));
        printf("Child Exit status code: %d\n", WEXITSTATUS(child_status));
    }
    else
    {
        printf("Inside Child process\n");
        printf("PID: %d and PPID: %d\n", getpid(), getppid());

        exit(2);
    }

    return 0;
}