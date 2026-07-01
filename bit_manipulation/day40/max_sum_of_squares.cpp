#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        // Array to count the number of set bits at each bit position (0-30)
        int bitCount[31] = {};
      
        // Count the number of 1s at each bit position across all numbers
        for (int num : nums) {
            for (int bitPos = 0; bitPos < 31; ++bitPos) {
                // Check if the bit at position bitPos is set
                if ((num >> bitPos) & 1) {
                    ++bitCount[bitPos];
                }
            }
        }
      
        // Initialize the answer and modulo constant
        long long answer = 0;
        const int MOD = 1e9 + 7;
      
        // Construct k numbers to maximize the sum of squares
        while (k--) {
            int constructedNum = 0;
          
            // Build a number by taking one bit from each position if available
            for (int bitPos = 0; bitPos < 31; ++bitPos) {
                if (bitCount[bitPos] > 0) {
                    // Set the bit at position bitPos
                    constructedNum |= (1 << bitPos);
                    // Decrement the count for this bit position
                    --bitCount[bitPos];
                }
            }
          
            // Add the square of the constructed number to the answer
            answer = (answer + 1LL * constructedNum * constructedNum) % MOD;
        }
      
        return answer;
    }
};