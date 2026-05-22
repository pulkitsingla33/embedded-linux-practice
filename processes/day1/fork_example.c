#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Hello World Main!\n");

    if(fork())
    {
        printf("Inside Parent process\n");
        printf("PID: %d and PPID: %d\n", getpid(), getppid());
    }
    else
    {
        printf("Inside Child process\n");
        printf("PID: %d and PPID: %d\n", getpid(), getppid());
    }

    return 0;
}