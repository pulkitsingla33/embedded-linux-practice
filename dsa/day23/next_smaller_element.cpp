#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> arr = {4, 5, 2, 10, 8};
    int arr_size = arr.size();

    vector<int> result(arr_size);

    stack<int> smaller_elements;

    for(int i = arr_size - 1; i >= 0; i--)
    {
        int current_num = arr[i];
        while(!smaller_elements.empty() && (current_num < arr[smaller_elements.top()]))
        {
            smaller_elements.pop();
        }
        if(smaller_elements.empty())
            result[i] = -1;
        else
            result[i] = arr[smaller_elements.top()];
        
        smaller_elements.push(i);
    }

    for(int num: result)
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}