// #include <bits/stdc++.h>
#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
    int arr[] = {2, 7, 11, 15};
    int target = 22;
    int arr_size = sizeof(arr)/sizeof(arr[0]);
    int index1 = 0, index2 = 0;

    unordered_map<int, int> element_map;

    for(int i = 0; i < arr_size; i++)
    {
        int num = arr[i];
        if(element_map.count(target - num))
        {
            index1 = i;
            index2 = element_map[(target - num)];
            break;
        }
        else
        {
            element_map.insert({num, i});
        }
    }

    cout << index1 << " " << index2 << endl;

    return 0;
}