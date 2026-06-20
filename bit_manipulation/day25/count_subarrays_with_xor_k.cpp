#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> arr= {4, 2, 2, 6, 4};
    int K = 6;

    unordered_map<int, int> xor_count;
    xor_count[0] = 1;
    int current_xor = 0;
    int totalSubarrays = 0;
    for(int i = 0; i < arr.size(); i++)
    {
        current_xor ^= arr[i];

        int target = current_xor ^ K;
        if(xor_count.find(target) != xor_count.end())
            totalSubarrays += xor_count[target];

        xor_count[current_xor]++;
    }

    cout << totalSubarrays << endl;

    return 0;
}