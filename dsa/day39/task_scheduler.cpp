#include <bits/stdc++.h>
using namespace std;

int leastInterval(vector<char>& tasks, int n) {
    int freq[26] = {0};
    for (int i = 0; i < tasks.size(); i++) {
        freq[tasks[i] - 'A']++;
    }
    int max_freq = 0;
    for (int i = 0; i < 26; i++) {
        max_freq = max(max_freq, freq[i]);
    }
    int max_freq_count = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] == max_freq) {
            max_freq_count++;
        }
    }
    return max((int)tasks.size(), (max_freq - 1) * (n + 1) + max_freq_count);
}

int main() {
    vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n = 2;
    cout << leastInterval(tasks, n) << endl; // Output: 8
    return 0;
}