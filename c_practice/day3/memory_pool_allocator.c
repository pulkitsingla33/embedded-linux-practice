#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define POOL_SIZE 20
#define BLOCK_SIZE 32

uint8_t *alloc_block(uint8_t *pool, uint8_t *free_list)
{
    if(!pool || !free_list)
        return NULL;

    for(int i = 0; i < POOL_SIZE; i++)
    {
        if(free_list[i] == 0)
        {
            printf("Block Number %d allocated\n", i);
            free_list[i] = 1;
            return (pool + i * BLOCK_SIZE);
        }
    }

    printf("Memory Full\n");
    return NULL;
}

uint8_t free_block(uint8_t *pool, uint8_t *block_address, uint8_t *free_list)
{
    if(!free_list || !pool || !block_address)
    {
        printf("Invalid Addresss\n");
        return 1;
    }

    if((block_address - pool) % 32 != 0)
    {
        printf("Invalid Block Address\n");
        return 1;
    }

    uint8_t block_index = (block_address - pool) / 32;
    if(block_index >= POOL_SIZE)
    {
        printf("Block Address out of bounds\n");
        return 1;
    }

    printf("Block Number %d deallocated\n", block_index);
    free_list[block_index] = 0;

    return 0;
}

void print_pool_status(uint8_t *free_list)
{
    for(int i = 0; i < POOL_SIZE; i++)
    {
        printf("Block %d:\t", i);
        if(free_list[i])
            printf("Used\n");
        else
            printf("Unused\n");
    }
    printf("\n");
}

int main()
{
    uint8_t memory_pool[POOL_SIZE * BLOCK_SIZE];
    uint8_t free_list[POOL_SIZE];

    for(int i = 0; i < POOL_SIZE; i++)
    {
        free_list[i] = 0;
    }

    uint8_t *block1 = alloc_block(memory_pool, free_list);
    if(!block1)
    {
        printf("Block 1 allocation failed\n");
        return -1;
    }
    uint8_t *block2 = alloc_block(memory_pool, free_list);
    if(!block2)
    {
        printf("Block 2 allocation failed\n");
        return -1;
    }
    uint8_t *block3 = alloc_block(memory_pool, free_list);
    if(!block3)
    {
        printf("Block 3 allocation failed\n");
        return -1;
    }
    uint8_t *block4 = alloc_block(memory_pool, free_list);
    if(!block4)
    {
        printf("Block 4 allocation failed\n");
        return -1;
    }

    print_pool_status(free_list);

    if(free_block(memory_pool, block2, free_list))
    {
        printf("Block 2 deallocation failed\n");
        return -1;
    }

    print_pool_status(free_list);
    
     if(free_block(memory_pool, block3, free_list))
    {
        printf("Block 3 deallocation failed\n");
        return -1;
    }

    print_pool_status(free_list);
    
    return 0;
}


