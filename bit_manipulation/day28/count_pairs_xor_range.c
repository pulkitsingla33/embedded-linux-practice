#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int count;
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode()
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->count = 0;
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

void addToTree(Node *head, int num)
{
    Node *currentNode = head;
    for(int i = 31; i >= 0; i--)
    {
        int bit = (num >> i) & 1;
        if(bit == 1)
        {
            if(!currentNode->right)
                currentNode->right = newNode();
            currentNode = currentNode->right;
        }
        else
        {
            if(!currentNode->left)
                currentNode->left = newNode();
            currentNode = currentNode->left;
        }
        currentNode->count++;
    }
}

int checkXorTree(Node *head, int num, int K)
{
    int count = 0;
    Node *currentNode = head;
    for(int i = 31; i >= 0; i--)
    {
        if(!currentNode)
            break;
        
        int K_bit = (K >> i) & 1;
        int num_bit = (num >> i) & 1;

        if(K_bit == 0)
        {
            if(num_bit == 1)
                currentNode = currentNode->right;
            else
                currentNode = currentNode->left;
        }
        else
        {
            if(num_bit == 1 && currentNode->right)
                count += currentNode->right->count;
            else if(num_bit == 0 && currentNode->left)
                count += currentNode->left->count;

            if(num_bit == 1)
                currentNode = currentNode->left;
            else
                currentNode = currentNode->right;
        }
    }

    return count;
}

int count_pairs(int *arr, int size, int K)
{
    Node *head = newNode();
    int current_count = 0;
    for(int i = 0; i < size; i++)
    {
        current_count += checkXorTree(head, arr[i], K);
        addToTree(head, arr[i]);
    }

    destroyTree(head);
    return current_count;
}

int main()
{
    int arr[] = {1,4,2,7};
    int arr_size = sizeof(arr)/sizeof(arr[0]);
    int L = 2, R = 6;

    
    int pairCount = count_pairs(arr, arr_size, (R + 1)) - count_pairs(arr, arr_size, L);

    printf("Total pairs in range are: %d\n", pairCount);

    return 0;
}