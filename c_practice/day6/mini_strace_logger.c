#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

//Example Output:
/*
open("test.txt") = 3
read(3, 128) = 64
close(3) = 0
*/

int main()
{
    int file_open, file_read, file_close;

    char *buffer[128];

    file_open = open("test.txt", O_RDONLY);
    file_read = read(file_open, buffer, 5);
    file_close = close(file_open);

    printf("open(\"test.txt\") = %d\n", file_open);
    printf("read(%d, buffer, 5) = %d\n", file_open, file_read);
    printf("close(%d) = %d\n", file_open, file_close);
    
    return 0;
}