#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> nums = {1,2,3,10,15};

    int max_xor = 0;
    int mask = 0;

    for(int i = 31; i >= 0; i--)
    {
        mask |= (1 << i);

        unordered_set<int> prefixes;
        for(int num: nums)
            prefixes.insert(num & mask);

        int candidateMax = max_xor | (1 << i);

        for(int prefix: prefixes)
        {
            int target = prefix ^ candidateMax;
            if(prefixes.count(target))
            {
                max_xor = candidateMax;
                break;
            }
        }
    }

    cout << "Max Xor is " << max_xor << endl;

    return 0;
}