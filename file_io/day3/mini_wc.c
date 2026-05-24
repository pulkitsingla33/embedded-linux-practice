#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Mention: <executable_name> <file_name>\n");
        return -1;
    }

    int read_fd = open(argv[1], O_RDONLY);
    if(read_fd == -1)
    {
        perror("File cannot be read");
    }

    char buffer[1024];
    ssize_t bytes_read;
    int word_count = 1;
    int line_count = 1;
    int char_count = 0;

    while((bytes_read = read(read_fd, buffer, sizeof(buffer) - 1)))
    {
        buffer[bytes_read] = '\0';

        char_count += bytes_read;

        for(int i = 0; i < bytes_read; i++)
        {
            if((buffer[i] == ' ') || (buffer[i] == '\n') || (buffer[i] == '\t') )
                word_count++;
            if(buffer[i] == '\n')
                line_count++;
        }
    }

    printf("Character count: %d\n", char_count);
    printf("Word count: %d\n", word_count);
    printf("Line count: %d\n", line_count);

    close(read_fd);

    return 0;
}