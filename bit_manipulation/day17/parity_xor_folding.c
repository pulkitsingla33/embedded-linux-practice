#include <stdio.h>

int main()
{
    int num = 133;

    num ^= num >> 16;
    num ^= num >> 8;
    num ^= num >> 4;
    num ^= num >> 2;
    num ^= num >> 1;
    num = num & 1;

    printf("Parity is: %d\n", num);

    return 0;
}