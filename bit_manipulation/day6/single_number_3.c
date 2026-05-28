#include <stdio.h>

int main()
{
    int arr[] = {1, 2, 3, 1, 2, 3, 5, 6, 10, 10, 5, 6, 11, 20, 11, 31};
    int arr_size = sizeof(arr)/sizeof(arr[0]);
    int total_xor = 0;


    for(int i = 0; i < arr_size; i++)
    {
        total_xor ^= arr[i];
    }

    int least_set_bit = total_xor & (-total_xor);

    int num1 = 0, num2 = 0;
    
    for(int i = 0; i < arr_size; i++)
    {
        if(arr[i] & least_set_bit)
            num1 ^= arr[i];
        else
            num2 ^= arr[i];
    }

    printf("The two distinct numbers are: %d and %d\n", num1, num2);
    return 0;
}