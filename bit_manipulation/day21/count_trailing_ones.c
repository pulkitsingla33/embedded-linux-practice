#include <stdio.h>

int main()
{
    int num = 0b11101110;

    int count = 0;
    while(num & 1)
    {
        num >>= 1;
        count++;
    }

    printf("Count is %d\n", count);

    return 0;
}