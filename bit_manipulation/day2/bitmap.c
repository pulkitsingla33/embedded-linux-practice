#include <stdio.h>
#include <stdint.h>


void set_bit(uint64_t *bitmap, int index)
{
    *bitmap |= (1LLU << index);
}

void clear_bit(uint64_t *bitmap, int index)
{
    *bitmap &= ~(1LLU << index);
}

uint8_t check_bit(uint64_t bitmap, int index)
{
    return ((bitmap >> index) & 0x1);
}

int main()
{
    uint64_t bitmap = 0x0123456789ABCDEF;

    printf("Bitmap is %lx\n", bitmap);

    set_bit(&bitmap, 62);
    printf("Bitmap after set bit %lx\n", bitmap);

    clear_bit(&bitmap, 0);
    printf("Bitmap after clear bit %lx\n", bitmap);

    printf("Check bit 1: %d\n", check_bit(bitmap, 1));
    printf("Check bit 2: %d\n", check_bit(bitmap, 2));
    printf("Check bit 3: %d\n", check_bit(bitmap, 3));

    return 0;
}