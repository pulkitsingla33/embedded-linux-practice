#include <bits/stdc++.h>
using namespace std;

int minSubArrayLen(int target, vector<int>& nums)
{
    int first = 0, last = 0;
    int arr_size = nums.size();
    int minSize = INT_MAX, sizeCounter = 0;
    int currentSum = 0;

    while(last < arr_size)
    {
        if(currentSum < target)
        {
            currentSum+= nums[last++];
            sizeCounter++;
        }

        while(currentSum >= target)
        {
            if(sizeCounter < minSize)
                minSize = sizeCounter;
            currentSum -= nums[first++];
            sizeCounter--;
        }
    }

    if(minSize == INT_MAX)
        return 0;
    else
        return minSize;
}

int main()
{
    vector<int> nums = {2,3,1,2,4,3};
    int target = 7;

    int minSize = minSubArrayLen(target, nums);
    cout << minSize << endl;

    return 0;
}