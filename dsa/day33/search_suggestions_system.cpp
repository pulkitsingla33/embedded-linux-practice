#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        // 1. Sort products lexicographically
        sort(products.begin(), products.end());
        
        vector<vector<string>> result;
        string prefix = "";
        
        // 2. Process each typed character
        for (char c : searchWord) {
            prefix += c;
            
            // 3. Binary search to find the first word where product >= prefix
            auto it = lower_bound(products.begin(), products.end(), prefix);
            
            vector<string> current_suggestions;
            
            // 4. Check up to the next 3 words from the starting iterator
            // We ensure we don't go out of bounds with `it + i != products.end()`
            for (int i = 0; i < 3 && (it + i) != products.end(); ++i) {
                const string& current_product = *(it + i);
                
                // Verify the word actually starts with the current prefix
                // Since C++ lacks a native .startswith(), we compare substrings
                if (current_product.substr(0, prefix.size()) == prefix) {
                    current_suggestions.push_back(current_product);
                } else {
                    // Since the array is sorted, if one fails, the rest will too
                    break; 
                }
            }
            
            result.push_back(current_suggestions);
        }
        
        return result;
    }
};