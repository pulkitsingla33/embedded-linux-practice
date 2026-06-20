#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public:
    int countTriplets(std::vector<int>& arr) {
        int n = arr.size();
        int total_triplets = 0;
        int pref_xor = 0;

        // Maps prefix XOR value to a pair: {frequency, sum_of_indices}
        std::unordered_map<int, std::pair<int, int>> map;
        
        // Base case: before starting, XOR is 0 at virtual index -1
        map[0] = {1, -1};

        for (int k = 0; k < n; ++k) {
            pref_xor ^= arr[k];

            if (map.count(pref_xor)) {
                int count = map[pref_xor].first;
                int sum_i = map[pref_xor].second;

                // Formula derived from: sum(k - i - 1) -> count * (k - 1) - sum_i
                total_triplets += count * (k - 1) - sum_i;
            }

            // Update the map with the current prefix XOR info
            map[pref_xor].first += 1;
            map[pref_xor].second += k;
        }

        return total_triplets;
    }
};

int main() {
    Solution solver;
    std::vector<int> arr = {2, 3, 1, 6, 7}; // Example array
    
    std::cout << "Total triplets: " << solver.countTriplets(arr) << std::endl;
    
    return 0;
}
