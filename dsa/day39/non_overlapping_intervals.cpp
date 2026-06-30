#include <bits/stdc++.h>
using namespace std;

int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(), [](vector<int> &a, vector<int> &b) {
        return a[0] < b[0];
    });
    int n = intervals.size();
    int ans = 0;
    for (int i = 1; i < n; i++) {
        if (intervals[i][0] < intervals[i-1][1]) {
            ans++;
            intervals[i][1] = min(intervals[i][1], intervals[i-1][1]);
        }
    }
    return ans;
}

int main() {
    vector<vector<int>> intervals = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
    cout << eraseOverlapIntervals(intervals) << endl; // Output: 1
    return 0;
}