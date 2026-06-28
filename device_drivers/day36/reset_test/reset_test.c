#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    uint64_t bytes_written;
    uint64_t bytes_read;
    uint64_t read_calls;
    uint64_t write_calls;
    uint64_t dropped_bytes;
} DriverStats;

#define GET_STATS    _IOR('a', 4, DriverStats)
#define RESET_DRIVER _IO('a', 6)

void print_stats(int fd, const char* label) {
    DriverStats s;
    if (ioctl(fd, GET_STATS, &s) < 0) {
        perror("GET_STATS failed");
        return;
    }
    
    printf("\n=== %s ===\n", label);
    printf("Bytes Written: %lu\n", s.bytes_written);
    printf("Bytes Read   : %lu\n", s.bytes_read);
    printf("Write Calls  : %lu\n", s.write_calls);
    printf("Read Calls   : %lu\n", s.read_calls);
    printf("Dropped Bytes: %lu\n", s.dropped_bytes);
    printf("===================\n");
}

int main() {
    int fd = open("/dev/mychardev", O_RDWR);
    if (fd < 0) {
        perror("Failed to open device");
        return -1;
    }

    printf("1. Injecting traffic to populate metrics...\n");
    write(fd, "KernelResetTest", 15);
    
    char buf[10];
    read(fd, buf, 5);

    // Verify statistics are populated
    print_stats(fd, "Stats Before Reset");

    printf("\n2. Issuing RESET_DRIVER IOCTL...\n");
    if (ioctl(fd, RESET_DRIVER) < 0) {
        perror("RESET_DRIVER failed");
        close(fd);
        return -1;
    }
    printf("Reset successful!\n");

    // Verify statistics are completely wiped
    print_stats(fd, "Stats After Reset");

    close(fd);
    return 0;
}