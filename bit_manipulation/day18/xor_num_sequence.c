#include <stdio.h>

int main()
{
    int N = 7;

    int rem = N % 4;
    int xor = 0;

    if(rem == 0)
        xor = N;
    else if(rem == 1)
        xor = 1;
    else if(rem == 2)
        xor = N + 1;
    else
        xor = 0;
}