#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>

int main()
{
    fd_set read_fds;
    struct timeval timeout;
    int retval;

    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);

    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    printf("Waiting for input..\n");
    fflush(stdout);

    retval = select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &timeout);
    if(retval == -1)
    {
        perror("select() error");
        exit(EXIT_FAILURE);
    }
    else if(retval == 0)
    {
        printf("Timeout\n");
    }
    else
    {
        if(FD_ISSET(STDIN_FILENO, &read_fds))
        {
            printf("Input received\n");

            char buffer[100];
            int bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
            if(bytes_read > 0)
            {
                buffer[bytes_read] = '\0';
                printf("Input is: %s\n", buffer);
            }
        }
    }



    return 0;
}