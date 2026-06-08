#include <stdio.h>

int main()
{
    int N = 8;
    int arr[] = {1, 2, 4, 6, 3, 8};

    int total_xor = 0;

    for(int i = 1; i <= N; i++)
        total_xor ^= i;

    for(int i = 0; i < N-2; i++)
        total_xor ^= arr[i];

    int mask = (total_xor) & (-total_xor);

    int num1 = 0, num2 = 0;

    for(int i = 1; i <= N; i++)
    {
        if(i & mask)
            num1 ^= i;
        else
            num2 ^= i;
    }

    for(int i = 0; i < N-2; i++)
    {
        if(arr[i] & mask)
            num1 ^= arr[i];
        else
            num2 ^= arr[i];
    }

    printf("Num 1 is: %d\nNum 2 is: %d\n", num1, num2);

    return 0;
}