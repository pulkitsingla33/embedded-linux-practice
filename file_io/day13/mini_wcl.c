#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s <filename.txt>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);

    char buffer[1024];
    ssize_t read_size = 0;
    int line_count = 0;

    char *line_loc = NULL;
    

    while(read_size = read(fd, buffer, sizeof(buffer)))
    {
        char *detect_buffer = buffer;
        while(line_loc = strchr(detect_buffer, '\n'))
        {
            line_count++;
            detect_buffer = line_loc + 1;
        }
    }

    printf("Line count is: %d\n", line_count);

    close(fd);
    
    return 0;
}