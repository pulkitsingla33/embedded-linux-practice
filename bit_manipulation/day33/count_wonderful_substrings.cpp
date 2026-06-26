#include <bits/stdc++.h>
using namespace std;

long long wonderfulSubstrings(string word)
{
    int mask = 0;

    vector<int> count(1024, 0);
    count[0] = 1;

    long long totalWonderful = 0;
    int currentMask = 0;

    for(char c: word)
    {
        currentMask ^= (1 << (c - 'a'));
        
        totalWonderful += count[currentMask];

        for(int i = 0; i < 10; i++)
        {
            totalWonderful += count[currentMask ^ (1 << i)];
        }

        count[currentMask]++;
    }

    return totalWonderful;
}

// Main function to test the logic
int main() {
    string word = "aba";
    
    long long result = wonderfulSubstrings(word);
    
    cout << "String: " << word << endl;
    cout << "Number of wonderful substrings: " << result << endl;
    
    return 0;
}