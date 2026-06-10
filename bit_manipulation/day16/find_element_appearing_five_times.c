#include <stdio.h>

int main()
{
    int arr[] = {2, 2, 1, 2, 1, 1, 1, 1};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    int ones = 0, twos = 0, threes = 0;

    for(int i = 0; i < arr_size; i++)
    {
        twos |= ones & arr[i];
        ones ^= arr[i];
        threes = ones & twos;
        ones &= ~threes;
        twos &= ~threes;
    }

    printf("Num appearing five times is: %d\n", twos);

    return 0;
}