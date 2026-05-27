#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    int N = 5;
    printf("Gray code sequence for N = %d:\n", N);

    for(int i = 0; i < (1 << N); i++)
    {
        printf("%x ", i ^ (i >> 1));
    }
    printf("\n");
    return 0;
}