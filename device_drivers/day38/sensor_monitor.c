#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <stdint.h>

#include "tempsensor_ioctl.h"

#define DEVICE_PATH "/dev/tempsensor"
#define READ_BUFFER_SIZE 256

int main(void)
{
    int fd;
    char rx_buffer[READ_BUFFER_SIZE];
    ssize_t bytes_read;

    fd = open(DEVICE_PATH, O_RDONLY);
    if(fd < 0)
    {
        fprintf(stderr, "Failed to open device %s: %s\n", DEVICE_PATH, strerror(errno));
        return EXIT_FAILURE;
    }

    unsigned int new_interval = 3000;

    if(ioctl(fd, TEMPSENSOR_SET_INTERVAL, &new_interval))
    {
        perror("IOCTL failed");
        return EXIT_FAILURE;
    }

    printf("Monitoring temperature sensor data. Press Ctrl+C to exit.\n");

    while(1)
    {
        memset(rx_buffer, 0, sizeof(rx_buffer));
        bytes_read = read(fd, rx_buffer, sizeof(rx_buffer) - 1);
        if(bytes_read < 0)
        {
            if(errno == EINTR)
            {
                break; // Interrupted by signal, retry
            }
            fprintf(stderr, "Failed to read from device: %s\n", strerror(errno));
            close(fd);
            return EXIT_FAILURE;
        }

        rx_buffer[bytes_read] = '\0';
        if(bytes_read > 0)
        {
            printf("%s", rx_buffer);
            printf("======================\n");
        }
    }

    printf("Exiting sensor monitor.\n");
    close(fd);
    return EXIT_SUCCESS;
}