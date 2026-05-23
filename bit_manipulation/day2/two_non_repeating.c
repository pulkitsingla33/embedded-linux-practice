#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    int arr[] = {1,2,3,2,1,4};
    int size = sizeof(arr)/sizeof(arr[0]);

    int all_xor = 0;

    for(int i = 0; i < size; i++)
    {
        all_xor ^= arr[i];
    }

    int set_bit = all_xor & ~(all_xor - 1);

    int num1 = 0;
    int num2 = 0;

    for(int i = 0; i < size; i++)
    {
        if(arr[i] & set_bit)
            num1 ^= arr[i];
        else
            num2 ^= arr[i];
    }

    printf("First number is %d\n", num1);
    printf("Second number is %d\n", num2);
    
    return 0;
}