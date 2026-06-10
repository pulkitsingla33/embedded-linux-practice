#include <stdio.h>

int main()
{
    int new_num = 0;
    int arr[] = {1, 3, 3, 3, 5};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    for(int i = 0; i < 31; i++)
    {
        int bit_counter = 0;
        for(int j = 0; j < arr_size; j++)
        {
            if(arr[j] & (1 << i))
                bit_counter++;
            else
                bit_counter--;
        }
        if(bit_counter > 0)
            new_num |= (1 << i);
    }

    printf("New num is: %d\n", new_num);

    return 0;
}