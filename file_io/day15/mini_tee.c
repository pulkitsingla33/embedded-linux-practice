#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s <filename.txt>\n", argv[0]);
        return 1;
    }

    int out_file = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(out_file < 0)
    {
        perror("Could not open file");
        return 1;
    }

    char buffer[1024];

    ssize_t read_bytes = read(STDIN_FILENO, buffer, sizeof(buffer));
    if(read_bytes < 0)
    {
        perror("Could not read STDIN");
        return 1;
    }

    ssize_t bytes_written_out = write(STDOUT_FILENO, buffer, read_bytes);
    if(bytes_written_out < 0)
    {
        perror("Write failed");
        return 1;
    }
    ssize_t bytes_written_file = write(out_file, buffer, read_bytes);
    if(bytes_written_file < 0)
    {
        perror("Write failed");
        return 1;
    }

    return 0;
}