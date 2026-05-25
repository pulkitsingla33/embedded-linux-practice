#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd = open("dup_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd < 0)
    {
        perror("Failed to create file");
        return 1;
    }

    if(dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("Failed to redirect stdout");
        close(fd);
        return 1;
    }


    printf("This text will now be redirected to output.txt\n");

    close(fd);

    fflush(stdout);
    close(STDOUT_FILENO);

    return 0;
}