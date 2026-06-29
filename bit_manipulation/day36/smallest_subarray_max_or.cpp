#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<int> smallestSubarrays(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<int> ans(n, 1);
        
        // Tracks the latest (nearest) index where each bit (0 to 29) was seen as 1.
        // Elements are up to 10^9, which fits within 30 bits (2^30 > 10^9).
        std::vector<int> last_seen_bit_idx(30, -1);

        // Traverse the array from right to left
        for (int i = n - 1; i >= 0; --i) {
            int shortest_end_idx = i;

            for (int b = 0; b < 30; ++b) {
                // If the b-th bit is set in the current number, update its latest position
                if ((nums[i] >> b) & 1) {
                    last_seen_bit_idx[b] = i;
                }
                
                // If this bit has been seen somewhere at or to the right of 'i',
                // it contributes to the maximum OR. We must extend our subarray to include it.
                if (last_seen_bit_idx[b] != -1) {
                    shortest_end_idx = std::max(shortest_end_idx, last_seen_bit_idx[b]);
                }
            }
            
            // The length of the smallest subarray starting at i is (end_index - start_index + 1)
            ans[i] = shortest_end_idx - i + 1;
        }

        return ans;
    }
};