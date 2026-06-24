#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> arr = {0,1,0,0,1,1};
    for(int i = 0; i < arr.size(); i++)
    {
        if(!arr[i])
            arr[i] = -1;
    }

    int prefix_sum = 0;
    int count = 0;

    unordered_map<int, int> prefix_map;
    prefix_map[0] = 1;
    for(int num: arr)
    {
        prefix_sum += num;
        if(prefix_map.find(prefix_sum) != prefix_map.end())
        {
            count += prefix_map[prefix_sum];
        }
        prefix_map[prefix_sum]++;
    }

    cout << count << endl;

    return 0;
}