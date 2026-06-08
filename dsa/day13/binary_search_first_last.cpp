#include <bits/stdc++.h>
using namespace std;

vector<int> searchRange(vector<int>& nums, int target)
{
    int first = 0;
    int last = nums.size() - 1;
    int firstIndex = -1, lastIndex = -1;

    int mid;

    if((first == last) && (target == nums[first]))
    {
        return {0, 0};
    }
    while(last > first)
    {
        mid = (first + last)/2;
        if(nums[mid] == target)
        {
            firstIndex = lastIndex = mid;
            break;
        }
        else if(target > nums[mid])
        {
            first = mid + 1;
        }
        else
        {
            last = mid - 1;
        }
    }

    while((firstIndex > 0))
    {
        if(nums[firstIndex - 1] == nums[firstIndex])
            firstIndex--;
        else
            break;
    }

    while((lastIndex < (nums.size() - 1)))
    {
        if(nums[lastIndex + 1] == nums[lastIndex])
            lastIndex++;
        else
            break;
    }

    vector<int> search_vals;
    search_vals = {firstIndex, lastIndex};

    return search_vals;
}

int main()
{
    vector<int> nums = {1};
    int target = 1;

    vector<int> searchVals = searchRange(nums, target);

    cout << "[" << searchVals[0] << ", " << searchVals[1] << "]\n";

    return 0;
}