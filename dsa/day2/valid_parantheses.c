#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *buffer;
    int top_index;
} MyStack;

int mystack_init(MyStack *stck, int size)
{
    if(stck == NULL)
        return -1;
    
    stck->buffer = malloc(size);
    if(!stck->buffer)
        return -1;

    stck->top_index = 0;

    return 0;
}

int main()
{
    char *str = "({[()]})";
    int str_length = strlen(str);

    MyStack mystack;

    mystack_init(&mystack, str_length);

    while(*str)
    {
        if((*str == '(') ||  (*str == '[') || (*str == '{'))
        {
            mystack.buffer[mystack.top_index] = *str;
            mystack.top_index++;
        }
        else if(*str == ')')
        {
            if(mystack.buffer[mystack.top_index-1] == '(')
            {
                mystack.buffer[--mystack.top_index] = 0;
            }
            else
            {
                printf("Invalid Parantheses\n");
                return 0;
            }
        }
        else if(*str == ']')
        {
            if(mystack.buffer[mystack.top_index-1] == '[')
            {
                mystack.buffer[--mystack.top_index] = 0;
            }
            else
            {
                printf("Invalid Parantheses\n");
                return 0;
            }
        }
        else if(*str == '}')
        {
            if(mystack.buffer[mystack.top_index-1] == '{')
            {
                mystack.buffer[--mystack.top_index] = 0;
            }
            else
            {
                printf("Invalid Parantheses\n");
                return 0;
            }
        }
        else
            return -1;

        str++;
    }

    printf("Valid Parantheses\n");

    
    return 0;
}