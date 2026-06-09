#include <bits/stdc++.h>
using namespace std;

void moveZeroes(vector<int>& nums)
{
    int z_index = -1, nz_index = 0;
    int arr_size = nums.size();

    for(int i = 0; i < arr_size; i++)
    {
        if((nums[i] == 0) && (z_index == -1))
        {
            z_index = i;
        }
        else if(nums[i] != 0)
        {
            nz_index = i;
        }

        if((nz_index > z_index) && (z_index != -1) && nums[nz_index] != 0)
        {
            nums[z_index] = nums[nz_index];
            nums[nz_index] = 0;
            z_index++;
        }
    }
}

int main()
{
    vector<int> nums = {4,2,4,0,0,3,0,5,1,0};
    moveZeroes(nums);

    for(int vals: nums)
    {
        cout << vals << " ";
    }
    cout << endl;

    return 0;
}