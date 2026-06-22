#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *left;
    struct Node *right;
}Node;

Node *newNode()
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

void destroyTree(Node *currentNode)
{
    if(currentNode == NULL)
        return;

    destroyTree(currentNode->left);
    destroyTree(currentNode->right);
    free(currentNode);
}

int main()
{
    int arr[] = {1, 2, 3, 4};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    int current_prefix = 0;

    Node *head = newNode();

    Node *currentNode = head;

    for(int i = 0; i <= arr_size; i++)
    {
        if(i == arr_size)
            current_prefix = 0;
        else
            current_prefix ^= arr[i];
        
        currentNode = head;
        for(int j = 31; j >= 0; j--)
        {
            if((current_prefix >> j) & 1)
            {
                if(!currentNode->right)
                {
                    currentNode->right = newNode();
                }
                currentNode = currentNode->right;
            }
            else
            {
                if(!currentNode->left)
                {
                    currentNode->left = newNode();
                }
                currentNode = currentNode->left;
            }
        }
    }

    int current_suffix = 0;
    int maxXor = 0;
    for(int i = arr_size; i >= 0; i--)
    {
        if(i < arr_size)
            current_suffix ^= arr[i];
        int currentXor = 0;
        currentNode = head;

        for(int j = 31; j >= 0; j--)
        {
            if((current_suffix >> j) & 1)
            {
                if(currentNode->left)
                {
                    currentNode = currentNode->left;
                    currentXor |= (1 << j);
                }
                else
                {
                    currentNode = currentNode->right;
                }
            }
            else
            {
                if(currentNode->right)
                {
                    currentNode = currentNode->right;
                    currentXor |= (1 << j);
                }
                else
                {
                    currentNode = currentNode->left;
                }
            }
        }
        if(currentXor > maxXor)
            maxXor = currentXor;
    }

    destroyTree(head);

    printf("Max Xor is: %d\n", maxXor);


    return 0;
}
