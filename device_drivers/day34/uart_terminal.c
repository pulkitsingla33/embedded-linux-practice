#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <poll.h>

struct termios orig_stdin_tty;

int configure_serial(int fd, speed_t baud_rate)
{
    struct termios tty;

    if(tcgetattr(fd, &tty) != 0)
    {
        perror("Error from tcgetattr");
        return -1;
    }

    cfsetispeed(&tty, baud_rate);
    cfsetospeed(&tty, baud_rate);

    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tty.c_oflag &= ~OPOST;

    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if(tcsetattr(fd, TCSANOW, &tty) != 0)
    {
        perror("Error from tcsetattr");
        return -1;
    }
    return 0;
}

void set_stdin_raw()
{
    struct termios tty;

    tcgetattr(STDIN_FILENO, &orig_stdin_tty);
    tty = orig_stdin_tty;
    tty.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void restore_stdin()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_stdin_tty);
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "Usage: %s <serial_device>\n", argv[0]);
        return 1;
    }

    const char *portname = argv[1];

    int serial_fd = open(portname, O_RDWR | O_NOCTTY);
    if(serial_fd < 0)
    {
        fprintf(stderr, "Error %d opening %s : %s\n", errno, portname, strerror(errno));
        return 1;
    }

    if(configure_serial(serial_fd, B115200) < 0)
    {
        close(serial_fd);
        return 1;
    }

    printf("Successfully opened %s at 115200 8N1. Press Ctrl+C to exit.\n", portname);

    set_stdin_raw();
    atexit(restore_stdin);

    struct pollfd fds[2];
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    fds[1].fd = serial_fd;
    fds[1].events = POLLIN;

    char buffer[256];

    while(1)
    {
        int ret = poll(fds, 2, -1);
        if(ret < 0)
        {
            perror("poll error");
            break;
        }

        if(fds[0].revents & POLLIN)
        {
            int n = read(STDIN_FILENO, buffer, sizeof(buffer));
            if(n > 0)
            {
                write(serial_fd, buffer, n);
            }
        }

        if(fds[1].revents & POLLIN)
        {
            int n = read(serial_fd, buffer, sizeof(buffer));
            if(n > 0)
            {
                write(STDOUT_FILENO, buffer, n);
            }
            else if(n == 0 || (n < 0 && errno != EAGAIN))
            {
                printf("\r\nSerial connection closed.\r\n");
                break;
            }
        }
    }

    close(serial_fd);
    return 0;
}