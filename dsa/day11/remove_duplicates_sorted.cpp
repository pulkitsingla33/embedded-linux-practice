#include <bits/stdc++.h>
using namespace std;

int removeDuplicates(vector<int>& arr)
{
    int n = arr.size();
    if(n <= 1)
        return n;

    int idx = 1;

    for(int i = 1; i < n; i++)
    {
        if(arr[i] != arr[i-1])
            arr[idx++] = arr[i];
    }

    return idx;
}

int main()
{

    vector<int> arr = {1, 1, 2, 2, 3, 4, 4, 5};
    int newSize = removeDuplicates(arr);

    for(int i = 0; i < newSize; i++)
    {
        cout << arr[i] << " ";
    }
    
    cout << endl;

    return 0;
}