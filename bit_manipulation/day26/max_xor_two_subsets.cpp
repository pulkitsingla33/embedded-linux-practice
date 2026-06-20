#include <iostream>
#include <vector>

using namespace std;

int maxXorTwoSubsets(const vector<int>& arr) {
    int max_xor = 0;
    
    // As proven by the XOR property, the maximum XOR of two subsets 
    // is simply the XOR sum of all elements in the array.
    for (int num : arr) {
        max_xor ^= num;
    }
    
    return max_xor;
}

int main() {
    vector<int> arr = {1, 2, 4, 8};
    
    cout << "Maximum XOR (Optimized): " << maxXorTwoSubsets(arr) << endl;
    // Expected Output: 15
    
    return 0;
}