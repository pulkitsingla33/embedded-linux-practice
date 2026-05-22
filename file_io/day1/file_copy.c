#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char buffer[1024];
    ssize_t bytes_read, bytes_written;

    if(argc != 3)
    {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return -1;
    }

    int read_fd = open(argv[1], O_RDONLY);
    if(read_fd == -1)
    {
        printf("Error while opening read file\n");
        return -1;
    }

    int write_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(write_fd == -1)
    {
        printf("Error while opening write file\n");
        return -1;
    }

    bytes_read = read(read_fd, buffer, sizeof(buffer) - 1);

    bytes_written = write(write_fd, buffer, bytes_read);    

    close(read_fd);
    close(write_fd);
    
    return 0;
}