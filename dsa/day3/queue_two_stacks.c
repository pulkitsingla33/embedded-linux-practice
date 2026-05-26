#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20

typedef struct Stack {
    int *data;
    int top;
    int capacity;
} Stack;

int stack_init(Stack *stack, int capacity)
{
    if(!stack) return -1;
    stack->data = (int *)malloc(capacity * sizeof(int));
    if (!stack->data) return -1;

    stack->top = -1;
    stack->capacity = capacity;
    return 0;
}

int stack_push(Stack *stack, int item)
{
    if(!stack) return -1;
    if (stack->top == stack->capacity - 1) {
        return 1; // Stack overflow
    }

    if(!stack->data) return -1;
    stack->data[++stack->top] = item;
    return 0;
}

int stack_pop(Stack *stack, int *item)
{
    if(!stack || !item) return -1;
    if (stack->top == -1) {
        return 1; // Stack underflow
    }

    *item = stack->data[stack->top--];
    return 0;
}

typedef struct Queue {
    Stack stack1;
    Stack stack2;
} Queue;

int queue_init(Queue *queue, int capacity)
{
    if(!queue) return -1;
    if (stack_init(&queue->stack1, capacity) == -1) return -1;
    if (stack_init(&queue->stack2, capacity) == -1) return -1;
    return 0;
}

int queue_push(Queue *queue, int item)
{
    if(!queue) return -1;
    printf("Pushing item: %d\n", item);
    return stack_push(&queue->stack1, item);
}

int queue_pop(Queue *queue, int *item)
{
    if(!(queue && item)) return -1;

    if(stack_pop(&queue->stack2, item) == 1)
    {
        printf("Transferring items from stack1 to stack2...\n");
        int transfer_item;
        while(stack_pop(&queue->stack1, &transfer_item)!= 1)
        {
            printf("Transferring item: %d\n", transfer_item);
            stack_push(&queue->stack2, transfer_item);
        }
    }
    else
    {
        return 0; // Successfully popped from stack2
    }

    return stack_pop(&queue->stack2, item);
}

void queue_print(Queue *queue)
{
    if(!queue) return;

    printf("Stack1: ");
    for (int i = 0; i <= queue->stack1.top; i++) {
        printf("%d ", queue->stack1.data[i]);
    }
    printf("\n");

    printf("Stack2: ");
    for (int i = 0; i <= queue->stack2.top; i++) {
        printf("%d ", queue->stack2.data[i]);
    }
    printf("\n");
}

int main()
{
    Queue queue;
    if(queue_init(&queue, MAX_SIZE) == -1) {
        perror("Failed to initialize queue");
        return 1;
    }

    queue_push(&queue, 1);
    queue_push(&queue, 2);
    queue_push(&queue, 3);

    int item;
    if(queue_pop(&queue, &item) == -1) {
        perror("Failed to pop from queue");
        return 1;
    }
    printf("Popped item: %d\n", item);

    if(queue_pop(&queue, &item) == -1) {
        perror("Failed to pop from queue");
        return 1;
    }
    printf("Popped item: %d\n", item);

    queue_push(&queue, 4);
    queue_push(&queue, 5);

    queue_print(&queue);

    return 0;
}