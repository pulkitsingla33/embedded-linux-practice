#include <bits/stdc++.h>
using namespace std;

vector<int> findNumofValidWords(vector<string>& words, vector<string>& puzzles) {
    // Step 1: Precompute the frequency of each word mask
    unordered_map<int, int> word_counts;
    for (const string& word : words) {
        int mask = 0;
        for (char c : word) {
            mask |= (1 << (c - 'a'));
        }
        // A puzzle has only 7 unique characters. 
        // If a word has more than 7 unique characters, it can never fit any puzzle.
        if (__builtin_popcount(mask) <= 7) {
            word_counts[mask]++;
        }
    }

    vector<int> result(puzzles.size(), 0);

    // Step 2: Process each puzzle
    for (int i = 0; i < puzzles.size(); i++) {
        int puzzle_mask = 0;
        for (char c : puzzles[i]) {
            puzzle_mask |= (1 << (c - 'a'));
        }

        int firstchar_mask = 1 << (puzzles[i][0] - 'a');
        int count = 0;

        // Step 3: Iterate through all sub-masks of the puzzle_mask
        int submask = puzzle_mask;
        while (submask > 0) {
            // Check if the submask contains the first character of the puzzle
            if ((submask & firstchar_mask) != 0) {
                // If this submask exists in our word map, add its frequency
                if (word_counts.count(submask)) {
                    count += word_counts[submask];
                }
            }
            // Bitwise trick to get the next submask
            submask = (submask - 1) & puzzle_mask;
        }

        result[i] = count;
    }

    return result;
}

int main()
{
    vector<string> words = {"apple","pleas","please"};
    vector<string> puzzles = {"aelwxyz","aelpxyz","aelpsxy","saelpxy","xaelpsy"};

    vector<int> result = findNumofValidWords(words, puzzles);

    for(int num: result)
        cout << num << " ";
    cout << endl;
    
    return 0;
}