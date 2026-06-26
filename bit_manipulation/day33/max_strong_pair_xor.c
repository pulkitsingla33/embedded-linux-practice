#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int max_num;
    struct Node *left;
    struct Node *right;
} Node;

void *newNode()
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->max_num = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void destroyTree(Node *head)
{
    if(head == NULL)
        return;

    destroyTree(head->left);
    destroyTree(head->right);
    free(head);
}

int checkTree(Node *head, int num)
{
    int currentXor = 0;
    Node *currentNode = head;
    for(int i = 31; i >= 0; i--)
    {
        if(!currentNode)
            return currentXor;

        int currentBit = (num >> i) & 1;
        if(currentBit == 1)
        {
            if(currentNode->left && (currentNode->left->max_num >= num))
            {
                currentNode = currentNode->left;
                currentXor |= 1 << i;
            }
            else if(currentNode->right && (currentNode->right->max_num >= num))
            {
                currentNode = currentNode->right;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if(currentNode->right && (currentNode->right->max_num >= num))
            {
                currentNode = currentNode->right;
                currentXor |= 1 << i;
            }
            else if(currentNode->left && (currentNode->left->max_num >= num))
            {
                currentNode = currentNode->left;
            }
            else
            {
                return 0;
            }
        }
    }

    return currentXor;
}

void insertTree(Node *head, int num)
{
    Node *currentNode = head;
    for(int i = 31; i >= 0; i--)
    {
        int currentBit = (num >> i) & 1;
        if(currentBit == 1)
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

        currentNode->max_num = num * 2;
    }
}

int maxXorStrongPair(int *nums, int size)
{
    Node *head = newNode();
    int maxXor = 0;
    for(int i = 0; i < size; i++)
    {
        int currentXor = checkTree(head, nums[i]);
        maxXor = (currentXor > maxXor) ? currentXor : maxXor;
        insertTree(head, nums[i]);
    }

    destroyTree(head);

    return maxXor;
}

int main()
{
    int nums[] = {1,1,3,9,10};
    int nums_size = sizeof(nums)/sizeof(nums[0]);
    int max_xor = maxXorStrongPair(nums, nums_size);

    printf("Max Strong Pair XOR is: %d\n", max_xor);

    return 0;
}