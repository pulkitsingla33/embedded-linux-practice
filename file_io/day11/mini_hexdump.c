#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        printf("Use: %s <file.bin>\n", argv[0]);
        return 1;
    }

    int c;
    unsigned int offset = 0;

    FILE *file = fopen(argv[1], "rb");
    if(!file)
    {
        perror("Error opening file");
        return 1;
    }

    while((c = fgetc(file)) != EOF)
    {
        if(offset % 5 == 0)
        {
            printf("%04X:", offset);
        }
        printf(" %02X", c);
        offset++;

        if(offset % 5 == 0)
            printf("\n");

    }

    if(offset % 5 != 0)
        printf("\n");
    

    fclose(file);
    
    return 0;
}