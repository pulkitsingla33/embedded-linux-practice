#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> arr = {3,2,3};

    unordered_map<int, int> arr_count;

    int majority_num = 0;

    for(int num: arr)
    {
        arr_count[num]++;
        if(arr_count[num] > (arr.size())/2)
            majority_num = num;
    }

    cout << "Majority element is: " << majority_num << endl;    

    return 0;
}