#include <stdio.h>

int main()
{
    int arr[] = {3, 4, 5};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    int totalSum = 0;

    for(int i = 0; i < 32; i++)
    {
        int one_count = 0;
        for(int j = 0; j < arr_size; j++)
        {
            if((arr[j] >> i) & 1)
                one_count++;
        }
        int zero_count = arr_size - one_count;
        totalSum += zero_count * one_count * (1 << i);
    }

    printf("Total sum is %d\n", totalSum);

    return 0;
}