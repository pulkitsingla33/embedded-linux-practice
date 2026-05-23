#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    printf("Entering Main\n");
    if(fork())
    {
        printf("Inside Parent after Fork 1\n");
        if(fork())
        {
            printf("Inside Parent after Fork 2\n");
            if(fork())
            {
                printf("Inside Parent after Fork 3\n");
                printf("PID: %d and PPID: %d of Parent\n", getpid(), getppid());
                sleep(rand() % 10);
                while(wait(NULL) > 0);
            }
            else
            {
                printf("Inside Child 3\n");
                printf("PID: %d and PPID: %d of Child 3\n", getpid(), getppid());
                sleep(rand() % 10);
                exit(3);
            }
        }
        else
        {
            printf("Inside Child 2\n");
            printf("PID: %d and PPID: %d of Child 2\n", getpid(), getppid());
            sleep(rand() % 10);
            exit(2);
        }
    }
    else
    {
        printf("Inside Child 1\n");
        printf("PID: %d and PPID: %d of Child 1\n", getpid(), getppid());
        sleep(rand() % 10);
        exit(1);
    }
    
    
    return 0;
}