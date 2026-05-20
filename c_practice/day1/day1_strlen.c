#include <stdio.h>

int my_strlen(char *str)
{
    int length = 0;

    while(*str++ != '\0')
        length++;
    
    return length;
}

int main()
{
    char *str = "Hello!";

    int length = 0;
    length = my_strlen(str);

    printf("Length is: %d\n", length);
}