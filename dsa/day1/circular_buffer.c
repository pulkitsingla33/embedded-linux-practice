#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

typedef struct{
    int *buffer;
    int head;
    int tail;
    int max_size;
} CircularBuffer;

int init(CircularBuffer *cb, int data)
{
    if(!cb)
        return -1;

    cb->max_size = BUFFER_SIZE;
    cb->buffer = malloc(sizeof(int) * cb->max_size);
    if(!cb->buffer)
    {
        printf("Memory Allocation Failed\n");
        return -1;
    }
    
    cb->head = 0;
    cb->tail = 1;
    cb->buffer[0] = data;

    return 0;
}

int is_full(CircularBuffer *cb)
{
    if(!cb)
        return -1;

    return ((cb->tail + 1) % cb->max_size == cb->head);
}

int is_empty(CircularBuffer *cb)
{
    if(!cb)
        return -1;

    return (cb->head == cb->tail);
}

int push(CircularBuffer *cb, int data)
{
    if(!cb)
        return -1;

    if(is_full(cb))
    {
        printf("Buffer Full\n");
        return -1;
    }

    printf("Push Data %d to index %d\n", data, cb->tail);
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % cb->max_size;

    return 0;
}

int pop(CircularBuffer *cb)
{
    if(!cb)
        return -1;

    if(is_empty(cb))
    {
        printf("Buffer Empty\n");
        return -1;
    }

    int data = cb->buffer[cb->head];
    printf("Pop Data %d from index %d\n", data, cb->head);
    cb->head = (cb->head + 1) % cb->max_size;
    return data;
}

void print(CircularBuffer *cb)
{
    if(!cb)
        return;

    int index = cb->head;
    if(is_empty(cb))
    {
        printf("Buffer Empty\n");
        return;
    }
    while(index != cb->tail)
    {
        printf("Element at index %d is %d\n", index, cb->buffer[index]);
        index = (index + 1) % cb->max_size;
    }
}


int main()
{
    CircularBuffer cb;

    if(init(&cb, 0) == -1)
    {
        printf("Initialization Failed\n");
        return -1;
    }

    for(int i = 0; i< 10; i++)
    {
        push(&cb, i);
    }

    for(int i = 0; i< 12; i++)
    {
        pop(&cb);
    }
    
    push(&cb, 100);

    free(cb.buffer);

    return 0;
}