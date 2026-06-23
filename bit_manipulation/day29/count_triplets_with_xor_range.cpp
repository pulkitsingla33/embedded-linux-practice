#include <iostream>
#include <vector>

using namespace std;

// Augmented Trie Node
struct TrieNode {
    int child[2];
    long long count;
    long long sum_i;
    
    TrieNode() {
        child[0] = child[1] = -1;
        count = 0;
        sum_i = 0;
    }
};

class Solution {
private:
    vector<TrieNode> trie;

    void insert(int val, int idx) {
        int curr = 0;
        for (int i = 31; i >= 0; --i) {
            int bit = (val >> i) & 1;
            if (trie[curr].child[bit] == -1) {
                trie[curr].child[bit] = trie.size();
                trie.emplace_back();
            }
            curr = trie[curr].child[bit];
            trie[curr].count++;
            trie[curr].sum_i += idx;
        }
    }

    // Returns the sum of contributions for all values strictly less than 'limit'
    long long queryUnderLimit(int val, int limit, int x_minus_1) {
        int curr = 0;
        long long ans = 0;
        
        for (int i = 31; i >= 0; --i) {
            if (curr == -1) break;
            
            int bit_val = (val >> i) & 1;
            int bit_limit = (limit >> i) & 1;

            if (bit_limit == 1) {
                // If we choose the branch matching 'bit_val', the XOR at this bit becomes 0.
                // 0 < 1, so the ENTIRE branch strictly satisfies the limit.
                int valid_branch = trie[curr].child[bit_val];
                if (valid_branch != -1) {
                    ans += (trie[valid_branch].count * x_minus_1) - trie[valid_branch].sum_i;
                }
                // Continue down the other branch to maintain the limit boundary
                curr = trie[curr].child[1 ^ bit_val];
            } else {
                // Limit bit is 0, we must match it (XOR = 0) to stay under/equal to the boundary
                curr = trie[curr].child[bit_val];
            }
        }
        return ans;
    }

public:
    long long countTriplets(vector<int>& arr, int L, int R) {
        trie.clear();
        trie.emplace_back(); // Root node at index 0
        
        long long total_triplets = 0;
        int current_prefix = 0;
        
        // P[0] = 0, its index is 0
        insert(current_prefix, 0);

        for (int x = 1; x <= arr.size(); ++x) {
            current_prefix ^= arr[x - 1];
            
            // Count valid configurations strictly < R + 1 and strictly < L.
            // The difference isolates the range [L, R] inclusive.
            long long count_R = queryUnderLimit(current_prefix, R + 1, x - 1);
            long long count_L = queryUnderLimit(current_prefix, L, x - 1);
            
            total_triplets += (count_R - count_L);
            
            // Insert current prefix and its index for future lookups
            insert(current_prefix, x);
        }
        
        return total_triplets;
    }
};