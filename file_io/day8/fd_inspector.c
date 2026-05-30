#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>

int main()
{
    int read_file, write_file;

    read_file = open("read_file.txt", O_RDONLY | O_CREAT, 0644);
    write_file = open("write_file.txt", O_WRONLY | O_CREAT, 0644);

    printf("Read file FD is %d\n", read_file);
    printf("Write file FD is %d\n", write_file);

    struct dirent *entry;
    DIR *dp = opendir("/proc/self/fd");
    if(dp == NULL)
    {
        perror("Failed to open /proc/self/fd");
        return 1;
    }

    printf("Open file descriptors:\n");
    while((entry = readdir(dp)) != NULL)
    {
        if(entry->d_name[0] != '.')
        {
            printf("%s\t", entry->d_name);
        }
    }
    printf("\n");

    closedir(dp);
    close(read_file);
    close(write_file);
    return 0;
}