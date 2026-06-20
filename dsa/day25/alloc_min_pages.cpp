#include <bits/stdc++.h>
using namespace std;

int findPages(vector<int> &arr, int k)
{
    if(arr.size() < k)
        return -1;

    int first = *max_element(arr.begin(), arr.end());
    int last = accumulate(arr.begin(), arr.end(), 0);

    int result = 0;
    
    while(first <= last)
    {
        int studentCount = 1;
        int mid = (first + last)/2;
        int sum = 0;

        for(int num: arr)
        {
            if(sum + num > mid)
            {
                sum = num;
                studentCount++;
            }
            else
            {
                sum += num;
            }
        }
        if(studentCount <= k)
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
    vector<int> arr = {15, 10, 19, 10, 5, 18, 7};
    int K = 5;

    cout << findPages(arr, K) << endl;

    return 0;
}