#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int count; // Tracks how many numbers pass through this node
    struct Node *left;  // Represents bit 0
    struct Node *right; // Represents bit 1
} Node;

// Helper to safely allocate and initialize a node
Node* createNode() {
    Node *node = (Node *)malloc(sizeof(Node));
    node->count = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void destroyTree(Node *currentNode)
{
    if(currentNode == NULL)
        return;

    destroyTree(currentNode->left);
    destroyTree(currentNode->right);
    free(currentNode);
}

void buildTree(Node *head, int num)
{
    Node *currentNode = head;
    for(int i = 31; i >= 0; i--)
    {
        int bit = (num >> i) & 1;
        if(bit == 1)
        {
            if(!(currentNode->right))
                currentNode->right = createNode();
            currentNode = currentNode->right;
        }
        else
        {
            if(!(currentNode->left))
                currentNode->left = createNode();
            currentNode = currentNode->left;
        }
        currentNode->count++; // Increment count for tracking
    }
}

int checkTree(Node *head, int num, int K)
{
    Node *currentNode = head;
    int count = 0;

    for(int i = 31; i >= 0; i--)
    {
        if (!currentNode) break;

        int bit_P = (num >> i) & 1;
        int bit_K = (K >> i) & 1;

        if (bit_K == 1)
        {
            // If K's bit is 1:
            // The branch matching bit_P gives XOR = 0 (strictly less than K).
            // We take all its counts immediately.
            if (bit_P == 1 && currentNode->right) {
                count += currentNode->right->count;
            } else if (bit_P == 0 && currentNode->left) {
                count += currentNode->left->count;
            }

            // Then we must CONTINUE down the opposite branch (where XOR = 1)
            if (bit_P == 1) currentNode = currentNode->left;
            else currentNode = currentNode->right;
        }
        else
        {
            // If K's bit is 0:
            // We can't add any branches yet. We must strictly follow 
            // the path that results in XOR = 0.
            if (bit_P == 1) currentNode = currentNode->right;
            else currentNode = currentNode->left;
        }
    }
    return count;    
}

int countSubarrays(Node *head, int *arr, int size, int K)
{
    int current_xor = 0;
    int count = 0;
    
    // Insert base case 0 into the Trie
    buildTree(head, 0);
    
    for(int i = 0; i < size; i++)
    {
        current_xor ^= arr[i];
        // Query the Trie with the current prefix XOR *before* inserting it
        count += checkTree(head, current_xor, K);
        buildTree(head, current_xor);
    }

    destroyTree(head);
    return count;
}

int main()
{
    Node *head = createNode();

    int arr[] = {4, 1, 3, 2};
    int k = 2;
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    int count = countSubarrays(head, arr, arr_size, k);
    printf("Count is %d\n", count); // Output: 3

    return 0;
}