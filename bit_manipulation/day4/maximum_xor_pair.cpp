#include <bits/stdc++.h>
using namespace std;

//Find pair of numbers in the array whose XOR is maximum and return the maximum XOR value, along with the pair of numbers.

vector<int> maxXor(vector<int>& arr)
{
    int res = 0, mask = 0;
    int num1 = 0, num2 = 0;

    unordered_map<int, int> prefixToNum;  // Map prefix to original array element

    for(int i = 30; i >= 0; i--)
    {
        mask |= (1 << i);
        prefixToNum.clear();

        for(int num: arr)
        {
            prefixToNum[num & mask] = num;
        }

        int cur = res | (1 << i);

        for(auto& p: prefixToNum)
        {
            int prefix = p.first;
            if(prefixToNum.count(cur ^ prefix))
            {
                res = cur;
                num1 = prefixToNum[prefix];
                num2 = prefixToNum[cur ^ prefix];
                break;
            }
        }
    }
    
    return {res, num1, num2}; // Return max XOR value and the pair
}

int main()
{
    vector<int> arr = {3, 10, 5, 25, 2, 8};
    vector<int> result = maxXor(arr);
    cout << "Maximum XOR value: " << result[0] << endl;
    cout << "Pair: (" << result[1] << ", " << result[2] << ")" << endl;
    return 0;
}