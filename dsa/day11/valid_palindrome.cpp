#include <bits/stdc++.h>
using namespace std;

bool isValidPalindrome(string s)
{
    if(s.compare("") == 0)
        return true;

    int first_index = 0;
    int last_index = s.length() - 1;

    do
    {

        if((s[first_index] >= 'A') && (s[first_index] <= 'Z'))
        {
            s[first_index] -= 'A' + 'a';
        }
        if((s[last_index] >= 'A') && (s[last_index] <= 'Z'))
        {
            s[last_index] -= 'A' + 'a';
        }

        if(!((s[first_index] >= 'a') && (s[first_index] <= 'z')))
            first_index++;
        if(!((s[last_index] >= 'a') && (s[last_index] <= 'z')))
            last_index --;

        if(s[first_index] != s[last_index])
            return false;

        first_index++;
        last_index--;
    }
    while(first_index <= last_index);

    return true;
}

int main()
{
    string s = "ma,layal,am";

    cout << isValidPalindrome(s) << endl;

    return 0;
}