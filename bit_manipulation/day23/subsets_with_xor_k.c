#include <stdio.h>

int main()
{
    int arr[] = {1, 2, 3};
    int arr_size = sizeof(arr)/sizeof(arr[0]);
    int mask_limit = 1 << arr_size;

    int K = 0;
    
    int count = 0;

    for(int i = 0; i < mask_limit; i++)
    {
        int currentXor = 0;
        int maskPos = 0;
        while(maskPos < arr_size)
        {
            if((i >> maskPos) & 1)
                currentXor ^= arr[maskPos];

            maskPos++;
        }

        if(currentXor == K)
            count++;
    }

    printf("Total subsets with XOR = %d are: %d\n", K, count);

    return 0;
}