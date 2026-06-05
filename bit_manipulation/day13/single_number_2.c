#include <stdio.h>

int main()
{
    int arr[] = {1, 1, 1, 2, 2, 2, 3,3,3, 40};
    int n = sizeof(arr) / sizeof(arr[0]);
    int ones = 0, twos = 0, threes = 0;

    for(int i = 0; i < n; i++)
    {
        twos |= ones & arr[i];
        ones ^= arr[i];
        threes = ones & twos;
        ones &= ~threes;
        twos &= ~threes;
    }

    printf("The single number is: %d\n", ones);
    return 0;
}