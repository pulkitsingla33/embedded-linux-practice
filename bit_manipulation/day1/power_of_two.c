#include <stdint.h>
#include <stdio.h>

uint8_t is_power_of_two(uint8_t num)
{
    return (!(num & (num-1)));
}

int main()
{
    uint8_t num = 129;

    uint8_t is_power = is_power_of_two(num);

    if(is_power)
        printf("Num:%u is power of two\n", num);
    else
        printf("Num:%u is not power of two\n", num);

    return 0;
}