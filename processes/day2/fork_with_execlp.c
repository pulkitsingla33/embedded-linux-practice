#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    printf("Starting main function execution\n");

    pid_t pid = fork();

    if(pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("Inside Child\n");
        execlp("ls", "ls", "-l", (char *)0);
    }
    else
    {
        printf("Waiting for child to terminate\n");
        wait(NULL);
    }

    printf("Exiting....\n");
    
    return 0;
}