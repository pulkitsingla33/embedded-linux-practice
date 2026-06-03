#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> nums1 = {4, 9, 5};
    vector<int> nums2 = {9, 4, 9, 8, 4};

    vector<int> intersection_nums;

    unordered_set<int> set_nums;

    for(int num: nums1)
    {
        set_nums.insert(num);
    }

    for(int num: nums2)
    {
        if(set_nums.count(num))
        {
            intersection_nums.push_back(num);
            set_nums.erase(num);
        }
    }

    for(int n: intersection_nums)
    {
        cout << n << " ";
    }
    cout << endl;

    return 0;
}