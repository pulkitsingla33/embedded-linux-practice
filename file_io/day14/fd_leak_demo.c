#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    DIR *dir;
    struct dirent *entry;
    dir = opendir("/proc/self/fd");
    if(dir == NULL)
    {
        perror("Failed to open /proc/self/fd");
        return EXIT_FAILURE;
    }


    int fd_list[5];

    for(int i = 0; i < 5; i++)
    {
        fd_list[i] = open(argv[1], O_RDONLY);
        if(fd_list[i] == -1)
        {
            perror("Failed to open file");
            closedir(dir);
            return EXIT_FAILURE;
        }

        rewinddir(dir);
        printf("Open file descriptors:\n");
        while((entry = readdir(dir)) != NULL)
        {
            printf("FD: %s\n", entry->d_name);
        }
        printf("\n");
    }

    
    for(int i = 0; i < 5; i++)
    {
        close(fd_list[i]);

        rewinddir(dir);
        printf("Open file descriptors:\n");
        while((entry = readdir(dir)) != NULL)
        {
            printf("FD: %s\n", entry->d_name);
        }
        printf("\n");
    }

    closedir(dir);

    return 0;
}