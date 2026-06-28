#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval)
{
    vector<vector<int>> post_insert;
    bool interval_added = false;

    for(vector<int> currentInterval: intervals)
    {
        if(interval_added)
        {
            post_insert.push_back(currentInterval);
            continue;
        }
        if(newInterval[0] > currentInterval[1])
        {
            post_insert.push_back(currentInterval);
        }
        else if(currentInterval[0] > newInterval[1])
        {
            interval_added = true;
            post_insert.push_back(newInterval);
            post_insert.push_back(currentInterval);
        }
        else
        {
            newInterval[0] = min(newInterval[0], currentInterval[0]);
            newInterval[1] = max(newInterval[1], currentInterval[1]);
        }
    }

    if(!interval_added)
    {
        post_insert.push_back(newInterval);
    }

    return post_insert;
}

int main()
{
    vector<vector<int>> intervals = {{1,5}};
    vector<int> newInterval = {6,8};

    vector<vector<int>> post_insert = insert(intervals, newInterval);

    for(vector<int> inserted_intervals : post_insert)
    {
        cout << "(" << inserted_intervals[0] << "," << inserted_intervals[1] <<")\n";
    }

    return 0;
}