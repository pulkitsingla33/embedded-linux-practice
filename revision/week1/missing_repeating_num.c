#include <stdio.h>

int main()
{
    int arr[] = {1,2,5,5,4,6};
    int N = 6;
    int repeating = 0, missing = 0;

    int arr_xor = 0, actual_xor = 0;

    for(int i = 0; i<N; i++)
    {
        arr_xor^= arr[i];
        actual_xor^= i + 1;
    }

    int two_num_xor = arr_xor ^ actual_xor;

    int mask = (two_num_xor) & (-two_num_xor);

    int num1 = 0, num2 = 0;
    for(int i = 0; i < N; i++)
    {
        if(arr[i] & mask)
            num1 ^= arr[i];
        else
            num2 ^= arr[i];

        if ((i+1) & mask)
            num1 ^= (i+1);
        else
            num2 ^= (i+1);
    }

    for(int i = 0; i < N; i++)
    {
        if(num1 == arr[i])
        {
            repeating = num1;
            missing = num2;
            break;
        }
        else if(num2 == arr[i])
        {
            repeating = num2;
            missing = num1;
            break;
        }
    }

    printf("Repeating Number is: %d\n", repeating);
    printf("Missing Number is: %d\n", missing);

    return 0;
}