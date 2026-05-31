#include <stdio.h>

int main()
{
    int a = 11;
    int b = 9;

    int numXor = a ^ b;
    int numLeastDiffBit = numXor & (-numXor);

    int bitPosCount = 0;

    while(numLeastDiffBit)
    {
        numLeastDiffBit = numLeastDiffBit >> 1;
        bitPosCount++;
    }

    printf("Position of lowest different bit: %d\n", bitPosCount);
}