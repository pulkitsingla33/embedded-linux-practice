#include <bits/stdc++.h>
using namespace std;

vector<int> getMaximumXor(vector<int>& nums, int maximumBit)
{
    vector<int> k_vals(nums.size());

    int target_mask = (1 << maximumBit) - 1;
    int current_prefix = 0;
    
    for(int i = 0; i < nums.size(); i++)
    {
        current_prefix ^= nums[i];
        k_vals[nums.size() - i - 1] = current_prefix ^ target_mask;
    }

    return k_vals;
}

int main()
{
    vector<int> nums = {0,1,2,2,5,7};
    int maximumBit = 3;

    vector<int> result = getMaximumXor(nums, maximumBit);

    for(int num: result)
        cout << num << " ";
    cout << endl;

    return 0;
}