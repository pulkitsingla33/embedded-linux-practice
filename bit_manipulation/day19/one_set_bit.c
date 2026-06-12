#include <stdio.h>

int main()
{
    int N = 20;

    int count = 0;
    while(N != 0)
    {
        count++;
        N >>= 1;
    }

    printf("Numbers with one set bits: %d\n", count);
    return 0;
}