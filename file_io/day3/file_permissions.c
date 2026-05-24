#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Execution format: <executable> <file_name>");
        return -1;
    }

    struct stat file_buffer;
    mode_t stat_var;

    if(access(argv[1], F_OK))
    {
        printf("File does not exist!\n");
        return -1;
    }
    else
    {
        if(!access(argv[1], R_OK))
            printf("Read allowed\n");
        if(!access(argv[1], W_OK))
            printf("Write allowed\n");
        if(!access(argv[1], X_OK))
            printf("Execute allowed\n");

        if(stat(argv[1], &file_buffer))
        {
            printf("Stat Access Failed!\n");
            return -1;
        }
        else
        {
            stat_var = file_buffer.st_mode;
            printf("Stats are: %x\n", stat_var);
        }
    }

    return 0;

}