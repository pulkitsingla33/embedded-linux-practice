#include <bits/stdc++.h>
using namespace std;

int search(vector<int>& nums, int target)
{
    int low = 0, high = nums.size() - 1;
    int mid;

    while(low <= high)
    {
        if(nums[high] >= nums[low])
            break;

        mid = (low + high)/2;

        if(nums[mid] > nums[high])
            low = mid + 1;

        else
            high = mid;
    }

    if(nums[low] == target)
        return low;
    
    if(low == 0)
        high = nums.size() - 1;
    else if(nums[0] < target)
        high = low - 1;
    else
    {
        low = low + 1;
        high = nums.size() - 1;
    }

    while(low <= high)
    {
        int mid = low + (high - low)/2;
        if(nums[mid] == target)
            return mid;
        if(nums[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}


int main()
{
    vector<int> arr = {5, 6, 7, 8, 9, 10, 1, 2, 3};
    int key = 3;
    cout << search(arr, key) << endl;

    return 0;
}