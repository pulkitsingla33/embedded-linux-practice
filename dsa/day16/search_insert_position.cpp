#include <bits/stdc++.h>
using namespace std;

int searchInsert(vector<int>& nums, int target)
{
    int first = 0, last = nums.size() - 1;
    int mid = 0;
    bool target_found = false;

    while(first < last)
    {
        mid = (first + last)/2;
        if(nums[mid] == target)
        {
            target_found = true;
            break;
        }
        else if(nums[mid] > target)
        {
            last = mid - 1;
        }
        else if(nums[mid] < target)
        {
            first = mid + 1;
        }
    }

    if(target_found)
        return mid;
    else if(first == last)
    {
        if(nums[first] >= target)
            return first;
        else
            return first + 1;
    }
    else
    return (last + 1);
}

int main()
{
    vector<int> nums = {1, 3, 5, 6};
    int target = 4;

    cout << searchInsert(nums, target) << endl;

    return 0;
}