#include <stdio.h>

int main()
{
    int num1 = 10, num2 = 20;

    printf("Before swap: Num1 = %d, Num2 = %d\n", num1, num2);

    num1 = num1 ^ num2;
    num2 = num2 ^ num1;
    num1 ^= num2;

    printf("After swap: Num1 = %d, Num2 = %d\n", num1, num2);
    
    return 0;
}