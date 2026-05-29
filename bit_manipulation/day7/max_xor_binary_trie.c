#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *left;
    struct node *right;
} node;

node *nodeCreate()
{
    node *newNode = (node *)(malloc(sizeof(node)));
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void insert(int x, node *head)
{
    node *current_node = head;

    for(int i = 30; i>= 0; i--)
    {
        int val = (x >> i) & 1;

        if(val == 0)
        {
            if(current_node->left == NULL)
                current_node->left = nodeCreate();

            current_node = current_node->left;
        }
        else
        {
            if(current_node->right == NULL)
                current_node->right = nodeCreate();

            current_node = current_node->right;
        }
    }
}

int main()
{
    int arr[] = {1,3,5};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    node *head = nodeCreate();
    head->left = NULL;
    head->right = NULL;

    for(int i = 0; i < arr_size; i++)
    {
        insert(arr[i], head);
    }

    int maxXor = 0;

    for(int i = 0; i < arr_size; i++)
    {
        int currXor = 0;
        int currNum = arr[i];

        node *currNode = head;

        for(int j = 30; j >= 0; j--)
        {
            int val = (currNum >> j) & 1;

            if(val == 0)
            {
                if(currNode->right)
                {
                    currXor |= (1 << j);
                    currNode = currNode->right;
                }
                else
                    currNode = currNode->left;
            }
            else
            {
                if(currNode->left)
                {
                    currXor |= (1 << j);
                    currNode = currNode->left;
                }
                else
                    currNode = currNode->right;
            }
        }

        maxXor = (currXor > maxXor)? currXor : maxXor;
    }

    printf("Max Xor is: %d\n", maxXor);    
    
    return 0;
}

