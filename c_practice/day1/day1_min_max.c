#include <stdio.h>

#define ARRAY_SIZE 10

int main()
{
    int array[ARRAY_SIZE];

    for(int i =0; i<ARRAY_SIZE; i++)
    {
        array[i] = i * 2 - 3;
    }
    
    int max = array[0];


    for(int i =0; i<ARRAY_SIZE; i++)
    {
        if(max < array[i])
            max = array[i];
    }

    printf("Max is: %d\n", max);

    return 0;
}