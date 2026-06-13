#include <bits/stdc++.h>
using namespace std;

int largestRectangleArea(vector<int> heights)
{
    int n = heights.size();

    stack<int> st;
    int maxArea = 0;

    for(int i = 0; i < n; i++)
    {
        while(!st.empty() && (heights[st.top()] >= heights[i]))
        {
            int tp = st.top();
            st.pop();

            int width = st.empty()? i : (i - st.top() - 1);
            int currentArea = heights[tp] * width;

            maxArea = (maxArea > currentArea)? maxArea : currentArea;         
        }
        st.push(i);
    }

    while(!st.empty())
    {
        int tp = st.top();
        st.pop();

        int width = st.empty()? n : (n - st.top() - 1);
        int currentArea = heights[tp] * width;

        maxArea = (maxArea > currentArea)? maxArea : currentArea;
    }

    return maxArea;
}

int main()
{
    vector<int> nums = {2,1,5,6,2,3};

    cout << largestRectangleArea(nums) << endl;

    return 0;
}