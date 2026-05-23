#include <stdio.h>
#include <stdint.h>

int main()
{
    uint16_t bitfield = 0xD69A;
    
    uint8_t loc1 = (uint8_t)((bitfield & 0x000F) >> 0);
    uint8_t loc2 = (uint8_t)((bitfield & 0x00F0) >> 4);
    uint8_t loc3 = (uint8_t)((bitfield & 0x0F00) >> 8);
    uint8_t loc4 = (uint8_t)((bitfield & 0xF000) >> 12);

    printf("Bitfield: 0x%04X\n", bitfield);
    printf("Location 1: 0x%02X\n", loc1);
    printf("Location 2: 0x%02X\n", loc2);
    printf("Location 3: 0x%02X\n", loc3);
    printf("Location 4: 0x%02X\n", loc4);
    
    return 0;
}