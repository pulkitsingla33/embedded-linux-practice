#include <stdio.h>

int main()
{
    int arr[] = {1,2,3,2,1,3,3};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    int total_xor = 0;
    for(int i = 0; i < arr_size; i++)
    {
        total_xor ^= arr[i];
    }

    printf("Number appearing odd number of times is %d\n", total_xor);

    return 0;
}