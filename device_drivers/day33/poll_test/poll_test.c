#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <string.h>

#define BUFFER_SIZE 256

int main()
{
    int fd;
    struct pollfd pfd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    fd = open("/dev/mychardev", O_RDWR);
    if(fd < 0)
    {
        perror("Failed to open device");
        return -1;
    }

    pfd.fd = fd;
    pfd.events = POLLIN;

    printf("waiting...\n");

    int ret = poll(&pfd, 1, -1);
    if(ret < 0)
    {
        perror("Poll error");
        close(fd);
        return -1;
    }

    if(pfd.revents & POLLIN)
    {
        printf("Data is available to read\n");
        memset(buffer, 0, BUFFER_SIZE);
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if(bytes_read < 0)
        {
            perror("Read error");
        }
        else
        {
            printf("Read %zd bytes: %s\n", bytes_read, buffer);
        }
    }

    close(fd);
    return 0;
}