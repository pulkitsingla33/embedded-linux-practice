#include <bits/stdc++.h>
using namespace std;

bool isAnagram(string s, string t)
{
    vector<int> freq(26);

    if(s.size() != t.size())
        return false;
    
    for(int i = 0; i <s.size(); i++)
    {
        freq[s[i] - 'a']++;
    }

    for(int i = 0; i < t.size(); i++)
    {
        freq[t[i] - 'a']--;
    }

    for(int num: freq)
    {
        if(num!= 0)
            return false;
    }

    return true;
}

int main()
{
    string s = "rat";
    string t = "car";

    cout << isAnagram(s, t) << endl;

    return 0;
}