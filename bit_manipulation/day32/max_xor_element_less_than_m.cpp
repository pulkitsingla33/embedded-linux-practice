#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Trie Node definition
struct Node {
    Node* links[2];
    Node() {
        links[0] = nullptr;
        links[1] = nullptr;
    }
};

class Trie {
private:
    Node* root;
public:
    Trie() {
        root = new Node();
    }
    
    // Insert a number into the Trie
    void insert(int num) {
        Node* node = root;
        // Start from the 31st bit down to 0
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (node->links[bit] == nullptr) {
                node->links[bit] = new Node();
            }
            node = node->links[bit];
        }
    }
    
    // Find the maximum XOR for a given number 'x'
    int getMax(int x) {
        Node* node = root;
        int max_xor = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (x >> i) & 1;
            // We want the opposite bit to maximize the XOR result
            if (node->links[1 - bit] != nullptr) {
                max_xor |= (1 << i);
                node = node->links[1 - bit];
            } else {
                node = node->links[bit]; // Forced to take the same bit
            }
        }
        return max_xor;
    }
};

// Structure to hold offline queries and original index
struct OfflineQuery {
    int m;
    int x;
    int index;
    
    // Sort queries based on 'm' in ascending order
    bool operator<(const OfflineQuery& other) const {
        return m < other.m;
    }
};

vector<int> maximizeXor(vector<int>& nums, vector<pair<int, int>>& queries) {
    // 1. Sort the input array
    sort(nums.begin(), nums.end());
    
    int q = queries.size();
    vector<OfflineQuery> offlineQueries(q);
    
    // 2. Map queries to our struct so we don't lose the original output order
    for (int i = 0; i < q; i++) {
        offlineQueries[i].x = queries[i].first;
        offlineQueries[i].m = queries[i].second;
        offlineQueries[i].index = i;
    }
    
    // 3. Sort the queries based on 'm'
    sort(offlineQueries.begin(), offlineQueries.end());
    
    vector<int> ans(q, -1);
    Trie trie;
    int idx = 0;
    int n = nums.size();
    
    // 4. Process each query incrementally
    for (int i = 0; i < q; i++) {
        int m = offlineQueries[i].m;
        int x = offlineQueries[i].x;
        int original_idx = offlineQueries[i].index;
        
        // Insert elements into the Trie strictly less than 'm'
        // (Note: Change to nums[idx] <= m if your specific platform requires an inclusive bound)
        while (idx < n && nums[idx] < m) {
            trie.insert(nums[idx]);
            idx++;
        }
        
        // If the Trie is not empty, calculate the max XOR. 
        // If it is empty, it remains -1 as initialized.
        if (idx > 0) {
            ans[original_idx] = trie.getMax(x);
        }
    }
    
    return ans;
}

int main() {
    vector<int> nums = {0, 1, 2, 3, 4};
    // Format: {x, m}
    vector<pair<int, int>> queries = {{3, 1}, {1, 3}, {5, 6}};
    
    vector<int> result = maximizeXor(nums, queries);
    
    // Expected Output: 3 3 7
    cout << "Output: [";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << (i == result.size() - 1 ? "" : ", ");
    }
    cout << "]" << endl;
    
    return 0;
}