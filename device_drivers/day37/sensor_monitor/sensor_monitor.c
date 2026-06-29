#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#define DEVICE_PATH "/dev/tempsensor"
#define READ_BUFFER_SIZE 256

void print_timestamp(void)
{
    time_t raw_time;
    struct tm *time_info;
    char time_str[30];

    time(&raw_time);
    time_info = localtime(&raw_time);

    strftime(time_str, sizeof(time_str), "[%Y-%m-%d %H:%M:%S]", time_info);
    printf("%s\n", time_str);
}

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
            print_timestamp();
            printf("%s\n", rx_buffer);
        }
    }

    printf("Exiting sensor monitor.\n");
    close(fd);
    return EXIT_SUCCESS;
}