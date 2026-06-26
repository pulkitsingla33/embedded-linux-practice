#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        // Step 1: Frequency counting
        vector<int> freq(26, 0);
        int max_freq = 0;
        
        for (char task : tasks) {
            freq[task - 'A']++;
            max_freq = max(max_freq, freq[task - 'A']);
        }
        
        // Step 2: Count how many tasks share the maximum frequency
        int max_count = 0;
        for (int count : freq) {
            if (count == max_freq) {
                max_count++;
            }
        }
        
        // Step 3: Apply the greedy formula
        int min_time = (max_freq - 1) * (n + 1) + max_count;
        
        // Return the maximum of calculated time or the raw length of tasks 
        // (in case no idle time is actually needed)
        return max((int)tasks.size(), min_time);
    }
};

int main() {
    Solution scheduler;
    vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n = 2;
    
    cout << "Minimum execution time: " << scheduler.leastInterval(tasks, n) << endl;
    
    return 0;
}