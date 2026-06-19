#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE_32 32
#define BLOCK_SIZE_64 64
#define BLOCK_SIZE_128 128
#define NUM_BLOCKS 32
#define SLAB_SIZE_32 (BLOCK_SIZE_32 * NUM_BLOCKS)
#define SLAB_SIZE_64 (BLOCK_SIZE_64 * NUM_BLOCKS)
#define SLAB_SIZE_128 (BLOCK_SIZE_128 * NUM_BLOCKS)

typedef struct BlockNode
{
    struct BlockNode *next;
} BlockNode;

static uint8_t mem_pool_32_byte[SLAB_SIZE_32] __attribute__((aligned(8)));
static uint8_t mem_pool_64_byte[SLAB_SIZE_64] __attribute__((aligned(8)));
static uint8_t mem_pool_128_byte[SLAB_SIZE_128] __attribute__((aligned(8)));

static BlockNode *free_list_32_head = NULL;
static BlockNode *free_list_64_head = NULL;
static BlockNode *free_list_128_head = NULL;

void slab_init(void)
{
    printf("Initializing Slabs\n");
    free_list_32_head = (BlockNode *)mem_pool_32_byte;
    free_list_64_head = (BlockNode *)mem_pool_64_byte;
    free_list_128_head = (BlockNode *)mem_pool_128_byte;

    BlockNode *current_32 = free_list_32_head;
    BlockNode *current_64 = free_list_64_head;
    BlockNode *current_128 = free_list_128_head;

    for(int i = 0; i < NUM_BLOCKS - 1; i++)
    {
        uint8_t *next_block_addr_32 = (uint8_t *)current_32 + BLOCK_SIZE_32;
        uint8_t *next_block_addr_64 = (uint8_t *)current_64 + BLOCK_SIZE_64;
        uint8_t *next_block_addr_128 = (uint8_t *)current_128 + BLOCK_SIZE_128;

        current_32->next = (BlockNode *)next_block_addr_32;
        current_64->next = (BlockNode *)next_block_addr_64;
        current_128->next = (BlockNode *)next_block_addr_128;
        
        current_32 = current_32->next;
        current_64 = current_64->next;
        current_128 = current_128->next;
    }

    current_32->next = NULL;
    current_64->next = NULL;
    current_128->next = NULL;
}

void *slab_alloc(int size)
{
    BlockNode *return_ptr;
    if(size <= BLOCK_SIZE_32 && free_list_32_head!= NULL)
    {
        return_ptr = free_list_32_head;
        free_list_32_head = free_list_32_head->next;
        printf("Allocated in Slab of 32 bytes\n");
    }
    else if(size <= BLOCK_SIZE_64 && free_list_64_head!= NULL)
    {
        return_ptr = free_list_64_head;
        free_list_64_head = free_list_64_head->next;
        printf("Allocated in Slab of 64 bytes\n");
    }
    else if(size <= BLOCK_SIZE_128 && free_list_128_head!= NULL)
    {
        return_ptr = free_list_128_head;
        free_list_128_head = free_list_128_head->next;
        printf("Allocated in Slab of 128 bytes\n");
    }
    else
        return NULL;

    return (void *)return_ptr;
}

void slab_free(void *ptr)
{
    if(ptr == NULL)
        return;

    for(BlockNode *current_node = free_list_32_head; current_node != NULL; current_node = current_node->next)
    {
        if(current_node == (BlockNode *)ptr)
            return;
    }
    for(BlockNode *current_node = free_list_64_head; current_node != NULL; current_node = current_node->next)
    {
        if(current_node == (BlockNode *)ptr)
            return;
    }
    for(BlockNode *current_node = free_list_128_head; current_node != NULL; current_node = current_node->next)
    {
        if(current_node == (BlockNode *)ptr)
            return;
    }

    uint8_t *current_ptr = (uint8_t *)ptr;

    if((current_ptr >= mem_pool_32_byte) && (current_ptr < mem_pool_32_byte + SLAB_SIZE_32))
    {
        BlockNode *free_node = (BlockNode *)ptr;
        free_node->next = free_list_32_head;
        free_list_32_head = free_node;
    }
    else if((current_ptr >= mem_pool_64_byte) && (current_ptr < mem_pool_64_byte + SLAB_SIZE_64))
    {
        BlockNode *free_node = (BlockNode *)ptr;
        free_node->next = free_list_64_head;
        free_list_64_head = free_node;
    }
    else if((current_ptr >= mem_pool_128_byte) && (current_ptr < mem_pool_128_byte + SLAB_SIZE_128))
    {
        BlockNode *free_node = (BlockNode *)ptr;
        free_node->next = free_list_128_head;
        free_list_128_head = free_node;
    }
    else
        return;
}

int main()
{
    slab_init();
    printf("Slabs Initiated Successfully\n");

    void *p1 = slab_alloc(20);
    printf("Pointer Allocated: %p\n", p1);
    void *p2 = slab_alloc(40);
    printf("Pointer Allocated: %p\n", p2);
    void *p3 = slab_alloc(60);
    printf("Pointer Allocated: %p\n", p3);
    void *p4 = slab_alloc(80);
    printf("Pointer Allocated: %p\n", p4);

    slab_free(p2);
    slab_free(p3);

    void *p5 = slab_alloc(50);
    printf("Pointer Allocated: %p\n", p5);

    slab_free(p1);
    slab_free(p4);
    slab_free(p5);

    return 0;
}
