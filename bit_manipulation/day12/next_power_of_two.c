#include <stdio.h>

unsigned int nextPowerOfTwo(unsigned int n)
{
    if((n & (n-1)) == 0)
        return n;

    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;

    n++;
    return n;
}

int main()
{
    int n = 65;
    printf("Next power of two is %d\n", nextPowerOfTwo(n));
    
    return 0;
}