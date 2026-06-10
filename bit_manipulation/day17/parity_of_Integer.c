#include <stdio.h>

int main()
{
    int num = 9;
    int parity = 0;

    while(num != 0)
    {
        parity = 1 - parity;
        num &= (num - 1);
    }

    printf("Parity is: %d\n", parity);
}