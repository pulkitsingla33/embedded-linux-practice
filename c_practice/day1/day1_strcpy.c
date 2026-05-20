#include <stdio.h>

char *my_strcpy(char *dest, char *src)
{
    char *dest_addr = dest;
    while(*dest++ = *src++);

    return dest_addr;
}

int main()
{
    char *src = "Hello World!";
    char dest[20];

    my_strcpy(dest, src);


    int i = 0;
    while(dest[i] != '\0')
    {
        printf("%c", dest[i]);
        i++;
    }
    printf("\n");

    return 0;
}