#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Usage: %s, <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    long end_pos = ftell(fp);

    long pos = end_pos - 1;
    int line_count = 0;

    while(pos >= 0)
    {
        fseek(fp, pos, SEEK_SET);
        int ch = fgetc(fp);

        if(ch == '\n')
        {
            if(pos != end_pos - 1)
            {
                line_count++;
                if(line_count == 10)
                    break;
            }
        }
        pos--;
    }

    fseek(fp, pos+1, SEEK_SET);

    char buffer[256];
    while(fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        fputs(buffer, stdout);
    }
    printf("\n");

    return 0;
}