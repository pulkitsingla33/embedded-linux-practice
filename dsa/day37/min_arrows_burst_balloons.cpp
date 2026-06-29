#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Custom comparator function to sort intervals by their end coordinates
bool compareEnd(const vector<int>& a, const vector<int>& b) {
    return a[1] < b[1];
}

int findMinArrowShots(vector<vector<int>>& points) {
    // Edge case: If there are no balloons, no arrows are needed
    if (points.empty()) return 0;

    // Sort the balloons based on their end coordinates
    sort(points.begin(), points.end(), compareEnd);

    // We need at least 1 arrow for the first balloon
    int num_arrows = 1;
    
    // Place the first arrow at the end coordinate of the first balloon
    int last_arrow_pos = points[0][1];

    // Iterate through the rest of the balloons
    for (size_t i = 1; i < points.size(); ++i) {
        // If the current balloon starts AFTER the last arrow position,
        // it cannot be burst by the previous arrow. We must fire a new one.
        if (points[i][0] > last_arrow_pos) {
            num_arrows++;
            last_arrow_pos = points[i][1]; // Place new arrow at this balloon's end
        }
    }

    return num_arrows;
}

int main() {
    // Example 1: Overlapping balloons
    vector<vector<int>> balloons1 = {{10, 16}, {2, 8}, {1, 6}, {7, 12}};
    cout << "Minimum arrows for Example 1: " << findMinArrowShots(balloons1) << endl; // Output: 2

    // Example 2: Non-overlapping balloons
    vector<vector<int>> balloons2 = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    cout << "Minimum arrows for Example 2: " << findMinArrowShots(balloons2) << endl; // Output: 4

    // Example 3: Completely overlapping balloons
    vector<vector<int>> balloons3 = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
    cout << "Minimum arrows for Example 3: " << findMinArrowShots(balloons3) << endl; // Output: 2

    return 0;
}