#include <stdio.h>

int main()
{
    int a = 10;
    int b = 20;

    int num_xor = a ^ b;
    int count = 0;
    
    while(num_xor != 0)
    {
        count++;
        num_xor &= (num_xor - 1);
    }

    printf("Differing bits: %d\n", count);

    return 0;
}