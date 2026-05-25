#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *my_calloc(size_t num_elements, size_t element_size)
{
    size_t total_size = num_elements * element_size;
    void *mem_address = malloc(total_size);
    if(!mem_address)
        return NULL;

    memset(mem_address, 0, total_size);
    
    return mem_address;
}

int main()
{
    int *calloc_address = (int *)my_calloc(8, sizeof(int));
    if(!calloc_address)
    {
        printf("Calloc failed!\n");
        return -1;
    }

    printf("Calloc successful\n");
    return 0;
}