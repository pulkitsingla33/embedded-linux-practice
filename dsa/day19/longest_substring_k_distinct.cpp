#include <bits/stdc++.h>
using namespace std;

int main()
{
    string str = "abcddefg";
    int k = 3;
    
    int first = 0, last = 0;
    int currentSize = 0, maxSize = 0, currentUnique = 0;
    unordered_map<char, int> distinct_chars;

    while(last < str.length())
    {
        if(distinct_chars[str[last]] == 0)
        {
            if(currentUnique < k)
            {
                currentUnique++;
                distinct_chars[str[last]]++;
                last++;
                currentSize++;
            }
            else
            {
                while(currentUnique >= k)
                {
                    if((--distinct_chars[str[first]]) == 0)
                    {
                        currentUnique--;
                    }
                    first++;
                    currentSize--;
                }
            }
        }
        else
        {
            distinct_chars[str[last]]++;
            last++;
            currentSize++;
        }

        if(currentSize > maxSize)
            maxSize = currentSize;
    }

    cout << maxSize << endl;

    return 0;
}