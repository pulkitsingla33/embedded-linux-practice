#include <stdio.h>
#include <stdlib.h>

typedef struct node_s
{
    struct node_s *left;
    struct node_s *right;
} Node;

void freeTree(Node *head)
{
    if(head == NULL)
        return;

    freeTree(head->left);
    freeTree(head->right);

    free(head);
}

int getMaxXor(int* arr, int arr_size)
{
    Node *head = malloc(sizeof(Node));

    for(int i = 0; i < arr_size; i++)
    {
        Node *current_node = head;
        int current_num = arr[i];

        for(int j = 31; j >= 0; j--)
        {
            if((current_num & (1 << j)) == 0)
            {
                if(current_node->left == NULL)
                    current_node->left = malloc(sizeof(Node));

                current_node = current_node->left;
            }
            else
            {
                if(current_node->right == NULL)
                    current_node->right = malloc(sizeof(Node));

                current_node = current_node->right;
            }
        }
    }

    int currentXor = 0, maxXor = 0;
    for(int i = 0; i < arr_size; i++)
    {
        int current_num = arr[i];
        Node *current_node = head;

        for(int j = 31; j >= 0; j--)
        {
            if((current_num & (1 << j)) == 0)
            {
                if(current_node->right != NULL)
                {
                    current_node = current_node->right;
                    currentXor |= 1 << j;
                }
                else
                    current_node = current_node->left;
            }
            else
            {
                if(current_node->left != NULL)
                {
                    current_node = current_node->left;
                    currentXor |= 1 << j;
                }
                else
                    current_node = current_node->right;
            }
        }

        if(currentXor > maxXor)
            maxXor = currentXor;
    }

    freeTree(head);

    return maxXor;
}

int main()
{
    int arr[] = {5, 6, 7};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    printf("Max Xor is %d\n", getMaxXor(arr, arr_size));

    return 0;
}