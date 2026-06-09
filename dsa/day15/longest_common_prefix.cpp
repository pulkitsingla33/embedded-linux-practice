#include <bits/stdc++.h>
using namespace std;

string longestCommonPrefix(vector<string>& strs)
{
    string current_prefix = strs[0];
    for(string current_str: strs)
    {
        string prefix = "";
        int i = 0;
        while(i < current_prefix.length() && i < current_str.length())
        {
            if(current_prefix[i] == current_str[i])
            {
                prefix += current_prefix[i];
                i++;
            }
            else
                break;            
        }
        current_prefix = prefix;
    }

    return current_prefix;
}

int main()
{
    vector<string> strs = {"dog", "racecar", "car"};

    cout << longestCommonPrefix(strs) << endl;
    return 0;
}