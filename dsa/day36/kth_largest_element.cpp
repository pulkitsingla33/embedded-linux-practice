#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> nums = {3,2,3,1,2,4,5,5,6};
    int k = 4;

    priority_queue<int> pq(nums.begin(), nums.end());

    int top_num = 0;
    while(k != 0)
    {
        top_num = pq.top();
        pq.pop();
        k--;
    }

    cout << top_num << endl;

    return 0;
}