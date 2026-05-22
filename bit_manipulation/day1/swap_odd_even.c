#include <stdio.h>
#include <stdint.h>

uint16_t swap_odd_even(uint16_t num)
{
    return ((num & 0xAAAA) >> 1) | ((num & 0x5555) << 1);
}

int main()
{
    uint16_t num = 0xAAAA;
    printf("Swapped value is: %x\n", swap_odd_even(num));
    return 0;
}