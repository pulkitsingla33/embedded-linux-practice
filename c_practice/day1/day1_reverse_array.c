#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 10

int main()
{
    int array[ARRAY_SIZE];
    int rev_array[ARRAY_SIZE];

    for(int i = 0; i < ARRAY_SIZE; i++)
        array[i] = i;

    
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        rev_array[i] = *(array + ARRAY_SIZE - 1 - i);
    }

    
    for(int i = 0; i<ARRAY_SIZE; i++)
        printf("i:%d, val:%d\n", i, rev_array[i]);

    
    return 0;
}