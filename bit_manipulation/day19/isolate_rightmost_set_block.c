#include <stdio.h>

int main()
{
    int num = 0b1110111000;

    int i = 0;
    while((num & (1 << i)) == 0)
        i++;

    int mask = 0;
    do
    {
        mask |= (1 << i);
        i++;
    }
    while((num & (1 << i)));

    int result = num & mask;

    printf("Result is %x\n", result);

    return 0;
}