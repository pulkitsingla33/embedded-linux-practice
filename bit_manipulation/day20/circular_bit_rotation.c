#include <stdio.h>
#include <stdint.h>

uint32_t rotate_left(uint32_t x, uint8_t k)
{
    return ((x >> (32 - k)) | (x << k));
}

uint32_t rotate_right(uint32_t x, uint8_t k)
{
    return ((x << (32 - k)) | (x >> k));
}

int main()
{
    uint32_t num = 0xABCDABCD;

    printf("Number %x left rotated by 4 is: %x\n", num, rotate_left(num, 4));
    printf("Number %x right rotated by 4 is: %x\n", num, rotate_right(num, 4));

    return 0;
}