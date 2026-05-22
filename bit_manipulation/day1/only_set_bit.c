#include <stdio.h>
#include <stdint.h>

int get_set_bit_pos(uint32_t num)
{
    if(num == 0 || (num & (num - 1)) != 0)
        return -1;

    int pos = 0;
    while((num & 1) == 0)
    {
        num >>= 1;
        pos++;
    }

    return pos;
}

int main()
{
    uint32_t num = 0x1000;
    printf("Set bit position is %d\n", get_set_bit_pos(num));
    return 0;
}