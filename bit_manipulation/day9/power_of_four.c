#include <stdio.h>

int main()
{
    int num = 64;

    int isPower = (num > 0) && ((num & (num - 1)) == 0) && ((num & 0xAAAAAAAA) == 0);

    if(isPower)
        printf("Number %d is power of 4\n", num);
    else
        printf("Number %d is not power of 4\n", num);
    
    return 0;
}