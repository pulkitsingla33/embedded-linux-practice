#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <unistd.h>

int main()
{
    struct pollfd fds[1];
    int timeout;
    int retval;

    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    fds[0].revents = 0;

    timeout = 5000;

    printf("Waiting for input...\n");
    fflush(stdout);

    retval = poll(fds, 1, timeout);
    if(retval == -1)
    {
        perror("poll() error");
        exit(EXIT_FAILURE);
    }
    else if(retval == 0)
    {
        printf("Timeout\n");
    }
    else
    {
        if(fds[0].revents & POLLIN)
        {
            printf("Input received\n");

            char buffer[100];
            int bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
            if(bytes_read > 0)
                buffer[bytes_read] = '\0';
        }
    }

    return 0;
}