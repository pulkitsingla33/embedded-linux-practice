#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

string reorganizeString(string s) {
    vector<int> count(26, 0);
    for (char c : s) count[c - 'a']++;

    // Max-heap stores pairs of {frequency, character}
    priority_queue<pair<int, char>> pq;
    for (int i = 0; i < 26; i++) {
        // If any character appears more than half the time (rounded up), it's impossible
        if (count[i] > (s.length() + 1) / 2) return "";
        if (count[i] > 0) pq.push({count[i], i + 'a'});
    }

    string res = "";
    pair<int, char> prev = {0, '#'}; // Placeholder for the blocked character

    while (!pq.empty()) {
        auto [freq, ch] = pq.top();
        pq.pop();
        
        res += ch;

        // If the previously used character still has count left, put it back
        if (prev.first > 0) pq.push(prev);

        // Decrease current character's count and set it as 'prev'
        prev = {freq - 1, ch};
    }

    return res;
}

int main() {
    cout << reorganizeString("aaabbc") << endl; // Output: abacab (or similar valid)
    return 0;
}