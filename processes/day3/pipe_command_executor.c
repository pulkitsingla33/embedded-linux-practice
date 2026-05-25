#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int pipe_fd[2];
    char buffer[20];

    char *command_str = "ls -l";

    if(pipe(pipe_fd) == -1)
    {
        perror("Failed to create pipe");
        return 1;
    }

    int pid = fork();

    if(pid > 0)
    {
        close(pipe_fd[0]);
        char *msg = command_str;
        write(pipe_fd[1], msg, strlen(msg)+1);
        close(pipe_fd[1]);
    }
    else
    {
        close(pipe_fd[1]);
        read(pipe_fd[0], buffer, sizeof(buffer));

        printf("Child Received: %s\n", buffer);
        close(pipe_fd[0]);

        execlp("/bin/sh", "sh", "-c", buffer, NULL);
        perror("Failed to execute command");
    }

    return 0;

}