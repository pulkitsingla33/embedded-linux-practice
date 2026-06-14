#include <stdio.h>
#include <stdint.h>

int main()
{
    uint32_t reg = 0xABCD1234;

    uint16_t device_id = reg >> 16;
    uint8_t flags = (reg >> 8) & (0xFF);
    uint8_t status = reg & 0xFF;

    printf("Device ID: %X\n", device_id);
    printf("Flags: %X\n", flags);
    printf("Status: %X\n", status);

    return 0;
}