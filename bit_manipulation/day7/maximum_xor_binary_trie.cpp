#include <bits/stdc++.h>
using namespace std;

class node
{
    public:
        node *left;
        node *right;
};

void insert(int x, node *head)
{
    node *curr = head;
    for(int i = 30; i >= 0; i--)
    {
        int val = (x >> i) & 1;
        if(val == 0)
        {
            if(!curr->left)
                curr->left = new node();
            
                curr = curr->left;
        }
        else
        {
            if(!curr->right)
                curr->right = new node();
            
                curr = curr->right;
        }
    }
}

int findMaximumXor(int arr[], int n)
{
    node *head = new node();
    int ans = 0;

    for(int i = 0; i<n; i++)
    {
        insert(arr[i], head);
    }

    for(int i = 0; i<n; i++)
    {
        int curr_xor = 0;
        int M = pow(2, 30);
        node *curr = head;

        for(int j = 30; j >= 0; j--)
        {
            int val = (arr[i] >> j) & 1;

            if(val == 0)
            {
                if(curr->right)
                {
                    curr_xor += M;
                    curr = curr->right;
                }
                else
                    curr = curr->left;
            }
            else
            {
                if(curr->left)
                {
                    curr_xor += M;
                    curr = curr->left;
                }
                else
                    curr = curr->right;
            }

            M/=2;
        }
        ans = max(ans, curr_xor);
    }

    return ans;
}

int main()
{
    int arr[] = {1,3,5};
    int maxXor = findMaximumXor(arr, 3);

    cout << "Maximum XOR is: " << maxXor << endl;
    
    return 0;
}