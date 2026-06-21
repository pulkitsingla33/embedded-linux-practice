#include <bits/stdc++.h>
using namespace std;

int aggressiveCows(vector<int> &stalls, int k)
{
    sort(stalls.begin(), stalls.end());

    int base_num = stalls[0];

    int first = 1;
    int last = stalls.back() - stalls.front();

    int result = 0;
    
    while(first <= last)
    {
        int mid = (first + last)/2;
        int count = 1;
        int last_placed = stalls[0];
        for(int i = 1; i < stalls.size(); i++)
        {
            if((stalls[i] - last_placed) >= mid)
            {
                count++;
                last_placed = stalls[i];
            }
        }
        if(count >= k)
        {
            result = mid;
            first = mid + 1;
        }
        else
        {
            last = mid - 1;
        }
    }

    return result;
}

int main()
{
    vector<int> stalls = {6, 4, 3, 16, 20, 7, 18, 10};
    int k = 5;

    cout << aggressiveCows(stalls, k) << endl;
    return 0;
}