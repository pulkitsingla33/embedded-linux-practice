#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} mynode;

mynode *HEAD = NULL;

void ll_init(int data)
{
    HEAD = malloc(sizeof(mynode));
    HEAD->data = data;
    HEAD->next = NULL;
}

void ll_add(int data)
{
    mynode *current_node = HEAD;

    while(current_node->next)
        current_node = current_node->next;

    mynode *new_node = malloc(sizeof(mynode));
    current_node->next = new_node;
    new_node->data = data;
    new_node->next = NULL;
}

void ll_delete(int index)
{
    mynode *current_node = HEAD;
    mynode *del_node = NULL;

    int i = 0;

    if(index == 0)
    {
        HEAD = HEAD->next;
        free(current_node);
    }
    else
    {
        while(i!=index-1)
        {
            i++;
            current_node = current_node->next;
        }

        del_node = current_node ->  next;
        current_node->next = current_node->next->next;
        free(del_node);
    }
}

void ll_print()
{
    mynode *current_node = HEAD;
    int index = 0;
    while(current_node)
    {
        printf("Index:%d, data:%d\n", index, current_node->data);
        index++;
        current_node = current_node->next;
    }
    printf("\n");
}

void ll_clear()
{
    mynode *current_node = HEAD;
    while(current_node->next)
    {
        current_node = current_node->next;
        free(HEAD);
        HEAD = current_node;
    }
}

int main()
{
    ll_init(0);

    ll_add(0);
    ll_add(10);
    ll_add(100);
    ll_print();

    ll_delete(2);
    ll_print();

    ll_clear();
    
    
    return 0;
}