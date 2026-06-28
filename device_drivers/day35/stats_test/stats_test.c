#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    uint64_t bytes_written;
    uint64_t bytes_read;
    uint64_t read_calls;
    uint64_t write_calls;
    uint64_t dropped_bytes;
} DriverStats;

#define GET_STATS _IOR('a', 4, DriverStats)

void print_driver_metrics(int fd)
{
    DriverStats current_stats;
    if (ioctl(fd, GET_STATS, &current_stats) == -1)
    {
        perror("ioctl GET_STATS failed");
        return;
    }

    printf("Driver Metrics:\n");
    printf("Bytes Written: %lu\n", current_stats.bytes_written);
    printf("Bytes Read: %lu\n", current_stats.bytes_read);
    printf("Read Calls: %lu\n", current_stats.read_calls);
    printf("Write Calls: %lu\n", current_stats.write_calls);
    printf("Dropped Bytes: %lu\n", current_stats.dropped_bytes);
}

int main()
{
    printf("[USER SPACE] GET_STATS Hex_Value: 0x%lx\n", (unsigned long)GET_STATS);

    int fd;
    char read_buffer[128];
    char large_overflow[1200];

    fd = open("/dev/mychardev", O_RDWR);
    if (fd < 0)
    {
        perror("Failed to open the device");
        return EXIT_FAILURE;
    }

    printf("Executing basic read/write operations...\n");

    write(fd, "KernelTelemetryEngine", 21);

    memset(read_buffer, 0, sizeof(read_buffer));
    read(fd, read_buffer, 15);
    printf("Read from device: %s\n", read_buffer);

    print_driver_metrics(fd);

    printf("\nFlooding driver with large writes to test dropped bytes...\n");
    memset(large_overflow, 'A', sizeof(large_overflow));

    write(fd, large_overflow, sizeof(large_overflow));

    print_driver_metrics(fd);

    close(fd);
    return EXIT_SUCCESS;
}