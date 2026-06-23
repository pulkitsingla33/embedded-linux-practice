#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> arr = {4, 2, 2, 6, 4};
    int K = 6;

    unordered_map<int, int> freq_map;
    freq_map[0] = 1;

    int current_xor = 0;
    int count = 0;
    for(int num: arr)
    {
        current_xor ^= num;
        int target = current_xor ^ K;
        if(freq_map.find(target) != freq_map.end())
        {
            count += freq_map[target];
        }

        freq_map[current_xor]++;
    }

    cout << count << endl;
    return 0;
}