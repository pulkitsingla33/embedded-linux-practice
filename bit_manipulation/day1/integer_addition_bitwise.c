#include <stdio.h>

int bitwise_addition_integer(int a, int b)
{
    while(b != 0)
    {
        int carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }

    return a;
}

int main()
{
    int a = 15, b = 27;
    printf("Sum of %d and %d is %d\n", a, b, bitwise_addition_integer(a, b));
    return 0;
}