#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *left;
    struct Node *right;
} Node;

void free_nodes(Node *head)
{
    if(head == NULL)
        return;

    free_nodes(head->left);
    free_nodes(head->right);

    free(head);
}

int main()
{
    int arr[] = {8, 1, 2, 12};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    int cum_xor = 0;
    int prefix_xor[arr_size];
    for(int i = 0; i < arr_size; i++)
    {
        cum_xor ^= arr[i];
        prefix_xor[i] = cum_xor;
    }

    Node *head = (Node *)malloc(sizeof(Node));
    head->left = NULL;
    head->right = NULL;

    for(int i = 0; i < arr_size; i++)
    {
        Node *current_node = head;
        for(int j = 31; j >= 0; j--)
        {
            if(((prefix_xor[i] >> j) & 1) == 1)
            {
                if(current_node->right == NULL)
                    current_node->right = (Node *)malloc(sizeof(Node));

                current_node = current_node->right;
            }
            else
            {
                if(current_node->left == NULL)
                    current_node->left = (Node *)malloc(sizeof(Node));

                current_node = current_node->left;
            }
        }
    }

    int max_xor = 0;
    for(int i = 0; i < arr_size; i++)
    {
        Node *current_node = head;
        int current_xor = 0;
        for(int j = 31; j >= 0; j--)
        {
            if((arr[i] >> j) & 1)
            {
                if(current_node->left != NULL)
                {
                    current_node = current_node->left;
                    current_xor |= (1 << j);
                }
                else
                    current_node = current_node->right;
            }
            else
            {
                if(current_node->right != NULL)
                {
                    current_node = current_node->right;
                    current_xor |= (1 << j);
                }
                else
                    current_node = current_node->left;
            }
        }

        if(current_xor > max_xor)
            max_xor = current_xor;
    }

    free_nodes(head);

    printf("Max Xor in Subarrays is %d\n", max_xor);

    return 0;
}