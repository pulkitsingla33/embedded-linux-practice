#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE_LEN 1024

int main(int argc, char *argv[])
{
    if(argc !=3)
    {
        printf("<executable> <file1> <file2>");
    }

    FILE *file1 = fopen(argv[1], "r");
    FILE *file2 = fopen(argv[2], "r");

    if(file1 == NULL || file2 == NULL)
    {
        if(file1)
            fclose(file1);
        if(file2)
            fclose(file2);
        perror("Error opening files");
        return 1;
    }

    char line1[MAX_LINE_LEN];
    char line2[MAX_LINE_LEN];
    int line_num = 1;

    while(1)
    {
        char *res1 = fgets(line1, sizeof(line1), file1);
        char *res2 = fgets(line2, sizeof(line2), file2);

        if(res1 == NULL && res2 == NULL)
        {
            break; // Both files have been read completely
        }
        
        if(res1 == NULL || res2 == NULL || strcmp(line1, line2) != 0)
        {
            printf("Line %d differs\n", line_num);
        }

        line_num++;
    }

    fclose(file1);
    fclose(file2);

    return 0;
}