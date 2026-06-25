#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> arr = {4,5,0,-2,-3,1};
    int K = 5;

    int current_sum = 0;
    unordered_map<int,int> remainders;
    remainders[0] = 1;
    int count = 0;

    for(int i = 0; i < arr.size(); i++)
    {
        current_sum += arr[i];
        int target = current_sum % K;
        if(remainders.find(target) != remainders.end())
        {
            count += remainders[target];
        }
        remainders[target]++;
    }

    cout << count << endl;

    return 0;
}