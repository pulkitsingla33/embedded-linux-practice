#include <bits/stdc++.h>
using namespace std;

int characterReplacement(string s, int k)
{
    vector<int> count(26, 0);
    int max_length = 0, max_freq = 0, left = 0;

    for(int right = 0; right < s.length(); right++)
    {
        count[s[right] - 'A']++;
        max_freq = max(max_freq, count[s[right - 'A']]);

        int window_length = right - left + 1;

        if(window_length - max_freq > k)
        {
            count[s[left] - 'A']--;
            left++;
        }

        max_length = max(max_length, right - left + 1);
    }

    return max_length;
}

int main()
{
    string s = "AABABBA";
    int k = 1;

    cout << characterReplacement(s, k) << endl;

    return 0;
}