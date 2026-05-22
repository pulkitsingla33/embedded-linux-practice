#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

typedef struct{
    int *buffer;
    int head;
    int tail;
    int max_size;
} CircularBuffer;

void init(CircularBuffer *cb, int data)
{
    cb->buffer = malloc(sizeof(int) * BUFFER_SIZE);
    cb->max_size = BUFFER_SIZE;
    
    cb->head = 0;
    cb->tail = 1;
    cb->buffer[0] = data;
}

int is_full(CircularBuffer *cb)
{
    return ((cb->tail + 1) % BUFFER_SIZE == cb->head);
}

int is_empty(CircularBuffer *cb)
{
    return (cb->head == cb->tail);
}

int push(CircularBuffer *cb, int data)
{
    if(is_full(cb))
    {
        printf("Buffer Full\n");
        return -1;
    }

    printf("Push Data %d to index %d\n", data, cb->tail);
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;

    return 0;
}

int pop(CircularBuffer *cb)
{
    if(is_empty(cb))
    {
        printf("Buffer Empty\n");
        return -1;
    }

    int data = cb->buffer[cb->head];
    printf("Pop Data %d from index %d\n", data, cb->head);
    cb->head = (cb->head + 1) % BUFFER_SIZE;
    return data;
}

void print(CircularBuffer *cb)
{
    int index = cb->head;
    if(is_empty(cb))
    {
        printf("Buffer Empty\n");
        return;
    }
    while(index != cb->tail)
    {
        printf("Element at index %d is %d\n", index, cb->buffer[index]);
        index = (index + 1) % BUFFER_SIZE;
    }
}


int main()
{
    CircularBuffer cb;

    init(&cb, 0);

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