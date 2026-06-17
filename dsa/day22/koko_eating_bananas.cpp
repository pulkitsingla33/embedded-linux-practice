#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

// function to check whether current speed is enough
bool check(vector<int>& arr, int mid, int k) {
    
    int totalHours = 0;
    for (int i = 0; i < arr.size(); i++) {
        totalHours += (arr[i] + mid - 1) / mid;
    }

    // return true if total hours needed is within limit
    return totalHours <= k;
}

// Function to find the minimum eating speed
int kokoEat(vector<int>& arr, int k) {
    int lo = 1;
    int hi = *max_element(arr.begin(), arr.end());
    int res = hi;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (check(arr, mid, k)) {
            // update result and try slower speed
            res = mid;       
            hi = mid - 1;
        } else {
             // need faster speed
            lo = mid + 1;    
        }
    }

    return res;
}

int main() {
    vector<int> arr = {5, 10, 3};
    int k = 4;
    cout << kokoEat(arr, k) << endl;
    return 0;
}