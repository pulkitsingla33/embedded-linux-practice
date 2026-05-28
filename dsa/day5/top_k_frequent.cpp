#include <bits/stdc++.h>
using namespace std;

//In this code, time complexity is O(N log N) due to the priority queue operations, where N is the number of unique elements in the input array. The space complexity is O(N) for storing the frequency map and the priority queue.
//There is another version of this code which uses a min-heap of size k to achieve O(N log k) time complexity, which is more efficient when k is small compared to N.
//Link: https://www.geeksforgeeks.org/dsa/find-k-numbers-occurrences-given-array/

vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int num : nums) {
        freq[num]++;
    }

    priority_queue<pair<int, int>> pq;
    for (const auto& [num, count] : freq) {
        pq.push({count, num});
    }

    vector<int> res;
    for (int i = 0; i < k; i++) {
        res.push_back(pq.top().second);
        pq.pop();
    }

    return res;
}

int main() {
    vector<int> nums = {1, 1, 1, 2, 2, 3};
    int k = 2;
    vector<int> res = topKFrequent(nums, k);
    for (int num : res) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}