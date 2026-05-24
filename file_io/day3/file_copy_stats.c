#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define APPEND_MODE 0

int main(int argc, char *argv[])
{

    if(argc != 4)
    {
        printf("Mention: <executable_name> <source_file> <destination_file> <buffer_size>\n");
        return -1;
    }

    int buffer_size = 0;
    sscanf(argv[3], "%d", &buffer_size);

    char buffer[buffer_size];
    ssize_t bytes_read, bytes_written;
    int total_bytes_written = 0;
    int total_read = 0;
    int write_fd;
    

    int read_fd = open(argv[1], O_RDONLY);
    if(read_fd == -1)
    {
        perror("Error opening read file\n");
        return -1;
    }

    if(APPEND_MODE)
    {
        write_fd = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, 0644);
    }
    else
    {
        if(open(argv[2], O_RDONLY) != -1)
        {
            printf("File already exists. Do you want to overwrite it? (y/n): ");
            char response;
            scanf(" %c", &response);
            if(response != 'y' && response != 'Y')
            {
                close(read_fd);
                return 0;
            }
        }
        write_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }
    if(write_fd == -1)
    {
        perror("Error opening write file\n");
        close(read_fd);
        return -1;
    }

    while((bytes_read = read(read_fd, buffer, sizeof(buffer) - 1)) > 0)
    {
        total_read ++;

        bytes_written = write(write_fd, buffer, bytes_read);
        total_bytes_written += bytes_written;
        if(bytes_written != bytes_read)
        {
            close(write_fd);
            close(read_fd);
            perror("Error while writing to file\n");
            return -1;
        }
    }

    close(read_fd);
    close(write_fd);

    printf("Total bytes written: %d\n", total_bytes_written);
    printf("Total read operations: %d\n", total_read);
    return 0;
}