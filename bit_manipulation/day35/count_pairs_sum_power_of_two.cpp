#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> nums = {1, 3, 7, 25};
    unordered_map<int, int> nums_set;
    int count = 0;

    nums_set[nums[0]] = 1;

    for(int i = 1; i < nums.size(); i++)
    {
        for(int j = 31; j >= 0; j--)
        {
            int target = (1 << j) - nums[i];
            if(target < 0)
                break;

            if(nums_set.find(target) != nums_set.end())
                count += nums_set[target];
        }

        nums_set[nums[i]]++;
    }

    cout << count << endl;
}