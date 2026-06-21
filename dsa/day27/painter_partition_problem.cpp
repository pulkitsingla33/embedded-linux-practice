#include <bits/stdc++.h>
using namespace std;

int minTime(vector<int>& arr, int k)
{
    int first = *max_element(arr.begin(), arr.end());
    int last = accumulate(arr.begin(), arr.end(), 0);

    int result = 0;

    while(first <= last)
    {
        int mid = (first + last)/2;
        int count = 1;
        int sum = 0;

        for(int num: arr)
        {
            if(sum + num > mid)
            {
                sum = num;
                count++;
            }
            else
            {
                sum += num;
            }
        }
        if(count <= k)
        {
            result = mid;
            last = mid - 1;
        }
        else
        {
            first = mid + 1;
        }
    }

    return result;
}

int main()
{
    vector<int> arr = {10, 20, 30, 40};
    int k = 2;

    cout << minTime(arr, k) << endl;

    return 0;
}