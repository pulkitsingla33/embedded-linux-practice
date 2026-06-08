#include <bits/stdc++.h>
using namespace std;

int findPeakElement(vector<int>& nums)
{
    int first = 0, last = nums.size() - 1;
    int mid;
    int peak_index = -1;
    while(first < last)
    {
        mid = (first + last)/2;
        if((mid > 0) && (mid < nums.size()))
        {
            if((nums[mid-1] < nums[mid]) && (nums[mid+1] < nums[mid]))
            {
                peak_index = mid;
                break;
            }
            else if(nums[mid - 1] > nums[mid])
                last = mid - 1;
            else if(nums[mid + 1] > nums[mid])
                first = mid + 1;
        }
        else if(mid == 0)
        {
            if(nums[1] < nums[0])
            {
                peak_index = 0;
            }
            else
                peak_index = 1;
            
            break;

        }
        else if(mid == (nums.size() - 1))
        {
            if(nums[mid] > nums[mid - 1])
                peak_index = mid;
            else
                peak_index = mid - 1;
            break;
        }
    }

    if(first == last)
        peak_index = first;

    return peak_index;
}

int main()
{
    vector<int> nums = {1, 2, 3, 1, 1, 1, 1};

    int peakElement = findPeakElement(nums);

    cout << peakElement << endl;

    return 0;
}