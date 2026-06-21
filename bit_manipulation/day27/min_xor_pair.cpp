#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void findMinXORPairs(vector<int>& arr) {
    int n = arr.size();
    
    // A pair requires at least 2 elements
    if (n < 2) {
        cout << "Array must have at least two elements." << endl;
        return;
    }

    // Step 1: Sort the array in ascending order (O(n log n))
    sort(arr.begin(), arr.end());

    int min_xor = INT_MAX;

    // Step 2: Iterate through adjacent elements to find the minimum XOR (O(n))
    for (int i = 0; i < n - 1; i++) {
        int current_xor = arr[i] ^ arr[i + 1];
        if (current_xor < min_xor) {
            min_xor = current_xor;
        }
    }

    // Step 3: Output the results
    cout << "Minimum XOR value: " << min_xor << endl;
    cout << "Pairs with the minimum XOR value:" << endl;

    // Do a second pass to print all pairs that equal the minimum XOR
    for (int i = 0; i < n - 1; i++) {
        if ((arr[i] ^ arr[i + 1]) == min_xor) {
            cout << "(" << arr[i] << ", " << arr[i + 1] << ")" << endl;
        }
    }
}

int main() {
    // The input array
    vector<int> arr = {1, 5, 8, 12, 20};
    
    findMinXORPairs(arr);
    
    return 0;
}