#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> nums = {100, 80, 60, 70, 60, 75, 85};
    vector<int> result(nums.size());

    stack<int> st;

    for(int i = 0; i < nums.size(); i++)
    {
        while(!st.empty() && nums[i] > nums[st.top()])
        {
            st.pop();
        }

        if(st.empty())
            result[i] = i + 1;
        else
            result[i] = i - st.top();

        st.push(i);
    }

    for(int val: result)
    {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}