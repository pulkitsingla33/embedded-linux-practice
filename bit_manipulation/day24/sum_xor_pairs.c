#include <stdio.h>

int main()
{
    int arr[] = {1, 2, 3};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    int sum = 0;
    for(int i = 0; i < 32; i++)
    {
        int count_one = 0;
        for(int j = 0; j < arr_size; j++)
        {
            if((arr[j] >> i) & 1)
                count_one++;
        }
        int count_zero = arr_size - count_one;
        sum += (count_one * count_zero) * (1 << i);
    }

    printf("Sum of All Xor Pairs is: %d\n", sum);

    return 0;
}