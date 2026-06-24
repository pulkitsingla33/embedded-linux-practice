#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdint.h>

#define SET_VALUE       _IOW('a', 1, int32_t *)
#define GET_VALUE       _IOR('a', 2, int32_t *)
#define CLEAR_BUFFER    _IO('a', 3)

int main()
{
    int fd;
    int32_t val_to_send = 123;
    int32_t val_to_receive = 0;

    printf("Opening /dev/mychardev..\n");
    fd = open("/dev/mychardev", O_RDWR, 0666);
    if(fd < 0)
    {
        perror("Failed to open device file");
        return -1;
    }

    printf("1. Calling IOCTL SET_VALUE with %d\n", val_to_send);
    if(ioctl(fd, SET_VALUE, &val_to_send) < 0)
    {
        perror("IOCTL SET_VALUE failed");
        close(fd);
        return -1;
    }

    printf("2. Calling IOCTL GET_VALUE\n");
    if(ioctl(fd, GET_VALUE, &val_to_receive) < 0)
    {
        perror("IOCTL GET_VALUE failed");
        close(fd);
        return -1;
    }

    printf("3. Calling IOCTL CLEAR_BUFFER...\n");
    if(ioctl(fd, CLEAR_BUFFER) < 0)
    {
        perror("IOCTL CLEAR_BUFFER failed");
        close(fd);
        return -1;
    }
    printf("Buffer cleared successfully\n");

    close(fd);
    printf("Closed device file\n");

    return 0;
}