#include <stdint.h>
#include <stdio.h>

uint8_t count_set_bits(uint8_t num)
{
    uint8_t count = 0;
    while(num!=0)
    {
        num &= (num-1);
        count++;
    }
    return count;
}

int main()
{
    uint8_t num = 0xFF;

    printf("Count is %u\n", count_set_bits(num));
    
    return 0;
}