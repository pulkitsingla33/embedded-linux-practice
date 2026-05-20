#include <stdio.h>

int my_strcmp(char *str1, char *str2)
{
    int diff = 0;
    while(*str1 && *str2)
    {
        diff = *str1 - *str2;
        if(diff!=0)
            break;
        
        str1++;
        str2++;
    }

    if(diff == 0)   //Unequal Lengths
    {
        if(*str1 && !(*str2))
            diff = *str1;
        else if(*str2 && !(*str1))
            diff = -(*str2);
    }

    return diff;
}

int main()
{
    char *str1 = "Hellosa";
    char *str2 = "Hellos";
    char *str3 = "World";

    printf("%d\n", my_strcmp(str1, str2));
    printf("%d\n", my_strcmp(str1, str3));
}