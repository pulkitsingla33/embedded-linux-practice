#include <stdio.h>
#include <stdint.h>

uint32_t reverse_bits(uint32_t num)
{
    num = ((num & 0xFFFF) << 16) | ((num & 0xFFFF0000) >> 16);
    num = ((num & 0xFF00FF00) >> 8) | ((num & 0xFF00FF) << 8);
    num = ((num & 0xF0F0F0F0) >> 4) | ((num & 0xF0F0F0F) << 4);
    num = ((num & 0xCCCCCCCC) >> 2) | ((num & 0x33333333) << 2);
    num = ((num & 0xAAAAAAAA) >> 1) | ((num & 0x55555555) << 1);

    return num;
}

int main()
{
    uint32_t my_num = 0xAAAA;

    printf("Reversed value is: %x\n",reverse_bits(my_num));
    
    return 0;