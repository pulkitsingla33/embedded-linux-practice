#include <stdio.h>

#define NUM 32

int main()
{
    int arr[NUM-1];
    int index = 0;

    int cum_xor = 0;

    for(int i = 1; i <= NUM; i++)
    {   
        cum_xor ^= i;
        if(i==20)
            continue;
        
        arr[index++] = i;
    }

    int arr_xor = 0;
    for(int i = 0; i < NUM - 1; i++)
    {
        arr_xor ^= arr[i];
    }

    int remaining_num = cum_xor ^ arr_xor;
    printf("Missing number is %d\n", remaining_num);
    
    return 0;
}