#include <stdio.h>

int extract_field(int value, int start, int width)
{
    int field_extract = value >> start;
    int mask = (1 << width) - 1;
    field_extract = field_extract & mask;

    return field_extract;
}

int main()
{
    int number = 0xD6;
    int start = 2, width = 4;

    printf("Fields after extraction is: %x\n", extract_field(number, start, width));
    
    return 0;
}