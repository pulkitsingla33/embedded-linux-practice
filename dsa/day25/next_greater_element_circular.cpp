#include <bits/stdc++.h>
using namespace std;

vector<int> nextGreaterElements(vector<int>& nums)
{
    int nums_size = nums.size();
    stack<int> st;
    vector<int> result(nums_size);

    for(int i = (nums_size * 2) - 1; i >= 0; i--)
    {
        int current_num = nums[i % nums_size];
        while(!st.empty() && (current_num >= nums[st.top()]))
        {
            st.pop();
        }

        if(i < nums_size)
        {
            if(st.empty())
                result[i] = -1;
            else
                result[i] = nums[st.top()];
        }

        st.push(i % nums_size);
    }

    return result;
}


int main()
{
    vector<int> nums = {1, 2, 3 ,4, 3};
    vector<int> result = nextGreaterElements(nums);

    for(int val: result)
    {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}