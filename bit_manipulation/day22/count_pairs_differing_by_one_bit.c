#include <stdio.h>

#define MAX_VAL 2048

int main()
{
    int arr[] = {1, 3, 5, 7};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    int hash_map[MAX_VAL] = {0};
    int pair_count = 0;

    for(int i = 0; i < arr_size; i++)
    {
        hash_map[arr[i] % MAX_VAL]++;

        for(int j = 0; j < 11; j++)
        {
            int current_num = arr[i] ^ (1 << j);
            if(hash_map[current_num % MAX_VAL])
                pair_count++;            
        }
    }

    printf("Pair Count is %d\n", pair_count);

    return 0;    
}