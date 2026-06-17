#include <stdio.h>
#include <stdlib.h>

struct node_s
{
    void *loc;
    int size;
    struct node_s *next;
    struct node_s *prev;
};

struct node_s *HEAD, *TAIL;

void *tracked_malloc(int size)
{
    void *ptr = malloc(size);

    struct node_s *new_node = (struct node_s*)malloc(sizeof(struct node_s));
    new_node->loc = ptr;
    new_node->size = size;
    new_node->next = NULL;

    if(HEAD == NULL)
    {
        new_node->prev = NULL;
        HEAD = new_node;
        TAIL = new_node;
    }
    else
    {
        new_node->prev = TAIL;
        TAIL->next = new_node;
        TAIL = new_node;
    }

    printf("ALLOC %p size=%d\n", (void *)ptr, size);
    return ptr;    
}

void tracked_free(void *ptr)
{
    struct node_s *current_node = HEAD;

    while((current_node->loc != ptr) && (current_node != NULL))
    {
        current_node = current_node->next;
    }

    if(current_node == NULL)
    {
        printf("Pointer not allocated\n");
        return;
    }
    
    if(current_node != HEAD)
        current_node->prev->next = current_node->next;
    else
        HEAD = current_node->next;

    if(current_node != TAIL)
        current_node->next->prev = current_node->prev;
    else
        TAIL = current_node->prev;

    free(ptr);
    free(current_node);

    printf("FREE %p\n", ptr);
}

void print_leaks()
{
    struct node_s *current_node = HEAD;

    if(current_node == NULL)
    {
        printf("No leaks\n");
        return;
    }
    
    printf("Leaks:\n");
    while(current_node != NULL)
    {
        printf("%p size=%d\n", current_node->loc, current_node->size);
        current_node = current_node->next;
    }
}

int main()
{
    int *ptr_list[6];
    int size = 32;
    for(int i = 0; i < 6; i++)
    {
        ptr_list[i] = (int *)tracked_malloc(size);
        size += 32;
    }

    for(int i = 0; i < 6; i+=2)
    {
        tracked_free((void *)ptr_list[i]);
    }

    print_leaks();

    for(int i = 1; i < 6; i+=2)
    {
        tracked_free((void *)ptr_list[i]);
    }

    print_leaks();

    return 0;
}