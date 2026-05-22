#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd[2];
    char buffer[20];

    if(pipe(fd) == -1)
        return 1;

    int pid = fork();

    if(pid > 0)
    {
        close(fd[0]);
        char *msg = "Hellow!";
        write(fd[1], msg, strlen(msg)+1);
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));

        printf("Child Received: %s\n", buffer);
        close(fd[0]);
    }

    return 0;
}