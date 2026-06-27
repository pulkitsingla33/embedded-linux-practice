#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countExcellentPairs(vector<int>& nums, int k) {
        // Remove duplicates by converting to set
        unordered_set<int> uniqueNums(nums.begin(), nums.end());

        // Array to count frequency of numbers with specific bit counts
        // cnt[i] = count of numbers having exactly i set bits
        vector<int> bitCountFrequency(32);

        // Count the frequency of each bit count in unique numbers
        for (int num : uniqueNums) {
            int setBits = __builtin_popcount(num);
            bitCountFrequency[setBits]++;
        }

        // Calculate the total count of excellent pairs
        long long excellentPairsCount = 0;

        // For each unique number, find all valid pairs
        for (int num : uniqueNums) {
            int currentBitCount = __builtin_popcount(num);

            // Check all possible bit counts for the second number in the pair
            for (int i = 0; i < 32; ++i) {
                // If the sum of bit counts meets the threshold k
                // (num1 OR num2) + (num1 AND num2) = bitCount(num1) + bitCount(num2)
                if (currentBitCount + i >= k) {
                    excellentPairsCount += bitCountFrequency[i];
                }
            }
        }

        return excellentPairsCount;
    }
};