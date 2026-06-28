#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    // 1. Define the input words
    std::vector<std::string> words = {"abcw", "baz", "foo", "bar", "xtfn", "abcdef"};
    
    int n = words.size();
    std::vector<int> masks(n, 0);
    std::vector<int> lengths(n, 0);

    // 2. Precompute bitmasks and lengths for each word
    for (int i = 0; i < n; ++i) {
        lengths[i] = words[i].length();
        for (char c : words[i]) {
            // Set the (c - 'a')-th bit to 1
            masks[i] |= (1 << (c - 'a'));
        }
    }

    int max_product = 0;

    // 3. Compare every unique pair of words
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // If the bitwise AND of their masks is 0, they share no characters
            if ((masks[i] & masks[j]) == 0) {
                int current_product = lengths[i] * lengths[j];
                max_product = std::max(max_product, current_product);
            }
        }
    }

    // 4. Output the result
    std::cout << "Maximum product of word lengths: " << max_product << "\n";

    return 0;
}