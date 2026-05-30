#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        printf("Enter command along with executable\n");
        return 1;
    }
    char *commands[argc];

    for(int i = 1; i<argc; i++)
    {
        commands[i-1] = argv[i];
    }
    commands[argc-1] = NULL;

    pid_t pid = fork();
    if(pid == -1)
    {
        perror("Fork unsuccessful");
        exit(1);
    }
    else if(pid == 0)
    {
        execvp(commands[0], commands);
        perror("Command execution failed");
        exit(1);
    }
    else
    {
        wait(NULL);
        printf("Command execution successful\n");
    }

    return 0;
}