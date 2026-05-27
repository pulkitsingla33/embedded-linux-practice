#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> mergeOverlap(vector<vector<int>>& arr) {

    // Sort intervals based on start values
    sort(arr.begin(), arr.end());
  
    vector<vector<int>> res;
    res.push_back(arr[0]);

    for (int i = 1; i < arr.size(); i++) {
        vector<int>& last = res.back();
        vector<int>& curr = arr[i];

        // If current interval overlaps with the last merged
        // interval, merge them 
        if (curr[0] <= last[1]) 
            last[1] = max(last[1], curr[1]);
        else 
            res.push_back(curr);
    }

    return res;
}

int main() {
    vector<vector<int>> arr = {{7, 8}, {1, 5}, {2, 4}, {4, 6}};
    vector<vector<int>> res = mergeOverlap(arr);

  	for (vector<int>& interval: res) 
        cout << interval[0] << " " << interval[1] << endl;
 
    return 0;
}