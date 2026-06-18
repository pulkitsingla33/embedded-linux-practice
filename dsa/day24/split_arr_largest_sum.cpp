#include <bits/stdc++.h>
using namespace std;

int splitArray(vector<int>& nums, int k)
{
    int first = *max_element(nums.begin(), nums.end());
    int last = accumulate(nums.begin(), nums.end(), 0);

    int current_min = last;

    while(first <= last)
    {
        int currentSplit = 1;
        int current_sum = 0;
        vector<int> subarray_sums(k);

        int mid = (first + last) / 2;
        for(int number: nums)
        {
            if(current_sum + number > mid)
            {
                current_sum = number;
                currentSplit++;
            }
            else
            {
                current_sum += number;
            }
            if(currentSplit <= k)
                subarray_sums[currentSplit - 1] = current_sum;
        }

        if(currentSplit > k)
        {
            first = mid + 1;
        }
        else
        {
            int max_split_sum = *max_element(subarray_sums.begin(), subarray_sums.end());
            if(max_split_sum < current_min)
                current_min = max_split_sum;

            last = mid - 1;
        }
    }

    return current_min;
}

int main()
{
    vector<int> nums = {1,2, 3, 4, 5};
    int k = 2;

    cout << "Minimized Largest Sum is: " << splitArray(nums, k) << endl;

    return 0;
}