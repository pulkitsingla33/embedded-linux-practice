#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> arr = {2, 1, 2, 4, 3};
    int arr_size = arr.size();

    vector<int> next_greater(arr_size);

    stack<int> greatest_nums;

    
    for(int i = arr_size - 1; i > 0; i--)
    {
        while(!greatest_nums.empty() && greatest_nums.top() <= arr[i])
            greatest_nums.pop();
            
        if(greatest_nums.empty())
        {
            next_greater[i] = -1;
        }
        else
        {
            next_greater[i] = greatest_nums.top();
        }

        greatest_nums.push(arr[i]);
    }

    return 0;
}