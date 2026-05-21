#include <stdint.h>
#include <stdio.h>

uint8_t set_nth_bit(uint8_t num, uint8_t n)
{
    return (num | (1 << n));
}

uint8_t clear_nth_bit(uint8_t num, uint8_t n)
{
    uint8_t mask = ~(1<<n);
    return num & mask;
}

uint8_t toggle_nth_bit(uint8_t num, uint8_t n)
{
    return (num ^ (1 << n));
}

uint8_t check_nth_bit(uint8_t num, uint8_t n)
{
    return ((num & (1 << n)) > 0);
}

int main()
{
    uint8_t number = 0xAA;

    printf("Original number: 0x%X\n", number);
    printf("Set 2nd bit: 0x%X\n", set_nth_bit(number, 2));
    printf("Clear 7th bit: 0x%X\n", clear_nth_bit(number, 7));
    printf("Toggle 1st bit: 0x%X\n", toggle_nth_bit(number, 1));
    printf("Check 3rd bit: %d\n", check_nth_bit(number, 3));
    
    return 0;
}