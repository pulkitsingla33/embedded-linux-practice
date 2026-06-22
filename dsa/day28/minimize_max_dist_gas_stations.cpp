// C++ program for the above approach
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Function to check if it is possible
// to add K points such that the maximum
// distance between adjacent points is D
 bool isPossible(double D, vector<int>& arr, int K) {
        // Stores the count of point used
        int used = 0;

        // Iterate over all given points
        for (int i = 0; i < (int)arr.size() - 1; ++i) {

            // Add number of points required
            // to be placed between ith
            // and (i+1)th point
            used += (int)((arr[i + 1] - arr[i]) / D);
        }

        // Return answer
        return used <= K;
    }

    // Function to find the minimum value of
    // maximum distance between adjacent points
    // after adding K points any where between
    double minMaxDist(vector<int>& stations, int K) {
        // Stores the lower bound and upper
        // bound of the given range
        double low = 0, high = 1e8;

        // Perform binary search
        while (high - low > 1e-6) {

            // Find the middle value
            double mid = (low + high) / 2.0;

            if (isPossible(mid, stations, K)) {

                // Update the current range
                // to lower half
                high = mid;
            }

            // Update the current range
            // to upper half
            else {
                low = mid;
            }
        }

        return low;
    }

// Driver Code
int main()
{
    vector<int>arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int K = 9;

    cout << minMaxDist(arr, K) << endl;

    return 0;
}