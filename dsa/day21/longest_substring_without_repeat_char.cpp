#include <bits/stdc++.h>
using namespace std;

int lengthOfLongestSubstring(string s)
{
    int first = 0, last = 0;
    unordered_set<char> st_chars;
    int maxLen = 0;

    while(last < s.length())
    {
        while(st_chars.count(s[last]))
        {
            st_chars.erase(s[first]);
            first++;
        }
        
        st_chars.insert(s[last++]);
        maxLen = (maxLen > (last - first))? maxLen : (last - first);
    }

    return maxLen;
}

int main()
{
    string s = "pwwkew";

    cout << lengthOfLongestSubstring(s) << endl;

    return 0;
}