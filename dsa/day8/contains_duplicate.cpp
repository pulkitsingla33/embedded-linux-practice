#include <bits/stdc++.h>
using namespace std;

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    bool is_duplciate = false;

    unordered_set<int> dup_arr;

    for(int i = 0; i < arr_size; i++)
    {
        if(!dup_arr.count(arr[i]))
            dup_arr.insert(arr[i]);
        else
        {
            is_duplciate = true;
            break;
        }
    }

    if(is_duplciate)
        cout << "Duplicate elements present in array" << endl;
    else
        cout << "No duplicate elements" << endl;
    
    return 0;
}