#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 64
#define NUM_BLOCKS 32
#define POOL_SIZE (BLOCK_SIZE * NUM_BLOCKS)

struct BlockNode
{
    struct BlockNode *next;
};

static uint8_t memory_pool[POOL_SIZE] __attribute__((aligned(8)));
static struct BlockNode *free_list_head = NULL;

void pool_init(void)
{
    free_list_head = (struct BlockNode *)memory_pool;
    struct BlockNode *current = free_list_head;

    for(int i = 0; i < NUM_BLOCKS - 1; i++)
    {
        uint8_t *next_block_addr = (uint8_t *)current + BLOCK_SIZE;
        current->next = (struct BlockNode *)next_block_addr;
        current = current->next;
    }

    current->next = NULL;
}

void *pool_alloc(void)
{
    if(free_list_head == NULL)
        return NULL;

    struct BlockNode *allocated_block = free_list_head;
    free_list_head = free_list_head->next;

    return (void *)allocated_block;
}

void pool_free(void *ptr)
{
    if(ptr == NULL)
        return;

    uint8_t *block_ptr = (uint8_t *)ptr;
    if(block_ptr < memory_pool || block_ptr >= (memory_pool + POOL_SIZE))
        return;

    for(struct BlockNode *current_node = free_list_head; current_node != NULL; current_node = current_node->next)
    {
        if(current_node == (struct BlockNode *)ptr)
            return;
    }

    struct BlockNode *free_node = (struct BlockNode *)ptr;
    free_node->next = free_list_head;
    free_list_head = free_node;
}

void pool_available()
{
    int i = 0;
    for(struct BlockNode *current_node = free_list_head; current_node != NULL; current_node = current_node->next)
    {
        printf("[FREE BLOCK %d]: %p\n", ++i, current_node);
    }
}

int main(void)
{
    pool_init();
    printf("Pool Initialized Successfully\n");

    void *p1 = pool_alloc();
    void *p2 = pool_alloc();

    printf("Allocated p1: %p\n", p1);
    printf("Allocated p2: %p\n", p2);

    pool_free(p1);
    printf("Freed p1\n");

    void *p3 = pool_alloc();
    printf("Allocated p3: %p\n", p3);

    pool_free(p2);
    pool_free(p3);

    pool_available();

    return 0;
}