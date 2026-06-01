#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int divide(int dividend, int divisor)
{
    if(dividend == INT_MIN && divisor == -1)
        return INT_MAX;

    int is_negative = (dividend < 0) ^ (divisor < 0);

    long long abs_dividend = llabs((long long)dividend);
    long long abs_divisor = llabs((long long)divisor);

    long long quotient = 0;

    for(int i = 31; i >= 0; i--)
    {
        if((abs_divisor << i) <= abs_dividend)
        {
            abs_dividend -= (abs_divisor << i);
            quotient += (1LL << i);
        }
    }

    return is_negative ? (int)(-quotient) : (int)quotient;
}

int main()
{
    int dividend = 43;
    int divisor = 8;

    int result = divide(dividend, divisor);
    printf("%d / %d = %d\n", dividend, divisor, result);

    return 0;
}