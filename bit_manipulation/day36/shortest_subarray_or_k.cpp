#include <bits/stdc++.h>
using namespace std;

int minimumSubarrayLength(vector<int>& nums, int k)
{
    int start = 0, end = 0;
    int current_or = 0;
    vector<int> bit_count(32,0);
    int currentSize = 0, minSize = INT_MAX;

    while(end != nums.size())
    {
        current_or |= nums[end];
        for(int i = 0; i < 32; i++)
        {
            ((nums[end] >> i) & 1) ? bit_count[i]++ : 0;
        }
        currentSize++;
        end++;

        while(current_or >= k && start < end)
        {
            if((currentSize != 0) && (currentSize < minSize))
                minSize = currentSize;
            int reset_mask = 0;
            for(int i = 0; i < 32; i++)
            {
                if(((nums[start] >> i) & 1))
                    bit_count[i]--;
                if(bit_count[i] == 0)
                    reset_mask |= 1 << i;
            }
            current_or &= ~reset_mask;
            start++;
            currentSize--;
        }
    }

    if(minSize == INT_MAX)
        minSize = -1;
    return minSize;
}

int main()
{
    vector<int> nums = {2,1};
    int k = 10;

    cout << minimumSubarrayLength(nums, k) << endl;

    return 0;
}