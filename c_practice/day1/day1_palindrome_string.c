#include <stdio.h>

int main()
{
    int palim = 0;
    char *str = "malayalama";

    int count = 0;

    while(str[count]!='\0')
    {
        count++;
    }
    
    for(int i =0; i<count; i++)
    {
        if(str[i] != str[count-i-1])
        {
            palim = 1;
            break;
        }
    }

    if(palim == 1)
        printf("Not Palindrome\n");
    else
        printf("Palindrome\n");

    return 0;
}