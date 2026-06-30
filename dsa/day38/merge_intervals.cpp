#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> merge(vector<vector<int>>& intervals)
{
    sort(intervals.begin(), intervals.end());

    int modify_index = 0;

    for(int i = 1; i < intervals.size(); i++)
    {
        if(intervals[i][0] <= intervals[modify_index][1])
        {
            intervals[modify_index][1] = max(intervals[modify_index][1], intervals[i][1]);
        }
        else
        {
            modify_index++;
            intervals[modify_index] = intervals[i];
        }
    }

    while(intervals.size() != modify_index + 1)
    {
        intervals.pop_back();
    }

    return intervals;
}

int main()
{
    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    vector<vector<int>> res = merge(intervals);

    for(vector<int> interval: res)
    {
        cout << interval[0] << " " << interval[1] << endl;
    }

    return 0;
}