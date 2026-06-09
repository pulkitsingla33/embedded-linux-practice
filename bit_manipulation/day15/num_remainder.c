#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int dividend = 15;
    int divisor  = 5;

    long long remainder;

    int is_negative = (dividend < 0) ^ (divisor < 0);

    long long abs_dividend = llabs((long long)dividend);
    long long abs_divisor = llabs((long long)divisor);

    if(dividend == 1)
        remainder = 0;
    else
    {
        for(int i = 31; i >= 0; i--)
        {
            if((abs_divisor << i) <= abs_dividend)
                abs_dividend -= (abs_divisor << i);
        }

        remainder = abs_dividend;
    }

    int remainder_int = is_negative ? (int)(-remainder) : (int)remainder;

    printf("Remainder is %d\n", remainder_int);

    return 0;

}