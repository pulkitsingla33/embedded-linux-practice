#include <bits/stdc++.h>
using namespace std;

int main()
{
    const char *word1 = "listent";
    const char *word2 = "silentt";

    unordered_map<int, int> word_map;

    char c = *word1;
    while(c)
    {
        word_map[c]++;
        c= *(++word1);
    }

    c = *word2;
    while(c)
    {
        word_map[c]--;
        c= *(++word2);
    }

    for(const auto &pair : word_map)
    {
        if(pair.second != 0)
        {
            cout << "Not an anagram" << endl;
            return 0;
        }
    }

    cout << "An anagram" << endl;
    return 0;
}