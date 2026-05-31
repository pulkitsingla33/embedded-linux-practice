#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define OPEN_LOG 0
#define READ_LOG 1
#define WRITE_LOG 2
#define CLOSE_LOG 3
#define WARNING_BUFFER_LOG 4
#define ERROR_LOG 5

void log_info(int log_type, int log_fd)
{
    char log_buf[1024];
    
    if(log_type == OPEN_LOG)
        strcpy(log_buf,"[INFO] File opened\n");
    else if(log_type == READ_LOG)
        strcpy(log_buf,"[INFO] Reading from file\n");
    else if(log_type == WRITE_LOG)
        strcpy(log_buf,"[INFO] Writing to file\n");
    else
        strcpy(log_buf,"[INFO] Closing file\n");

    printf("%s", log_buf);
    write(log_fd, log_buf, strlen(log_buf));
}

void log_warning(int log_type, int log_fd)
{
    char log_buf[1024];
    
    if(log_type == WARNING_BUFFER_LOG)
        strcpy(log_buf, "[WARNING] Buffer almost full\n");

    printf("%s", log_buf);
    write(log_fd, log_buf, strlen(log_buf) + 1);
}

void log_error(int log_type, int log_fd)
{
    char log_buf[1024];
    
    if(log_type == ERROR_LOG)
        strcpy(log_buf, "[ERROR] Connection failed\n");

    printf("%s", log_buf);
    write(log_fd, log_buf, strlen(log_buf) + 1);
}

int main()
{
    
    
    int log_fd = open("app.log", O_WRONLY | O_TRUNC | O_CREAT, 0644);

    int num_buf[10];
    for(int i = 0; i < 10; i++)
    {
        num_buf[i] = i;
        if(i == 8)
            log_warning(WARNING_BUFFER_LOG, log_fd);
    }

    int file_fd = open("input.txt", O_RDWR, 0644);
    if(file_fd == -1)
    {
        log_error(ERROR_LOG, log_fd);
        return 1;
    }
    log_info(OPEN_LOG, log_fd);

    close(file_fd);
    log_info(CLOSE_LOG, log_fd);

    close(log_fd);

    return 0;
}