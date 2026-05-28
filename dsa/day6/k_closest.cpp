#include <bits/stdc++.h>
using namespace std;

vector<int> printKClosest(vector<int> arr, int k, int x)
{
    int n = arr.size();
    int i = 0;
    int low = 0, high = n - 1, pos = -1;

    while(low <= high)
    {
        int mid = (low + high) / 2;
        if(arr[mid] < x)
        {
            pos = mid;
            low = mid + 1;
        }
        else
            high = mid - 1;
    }

    int left = pos, right = pos + 1;
    vector<int> result;

    if(arr[right] == x)
        right++;

    while((result.size() < k) && (left >= 0 && right < n))
    {
        if(abs(arr[left] - x) <= abs(arr[right] - x))
            result.push_back(arr[left--]);
        else
            result.push_back(arr[right++]);
    }

    while((result.size() < k) && left >= 0)
        result.push_back(arr[left--]);

    while((result.size() < k) && right < n)
        result.push_back(arr[right++]);

    sort(result.begin(), result.end());

    return result;
}

int main()
{
    vector<int> arr = {1, 2, 3, 4, 5, 10, 20, 30, 31, 32};
    int k = 5, x = 20;

    vector<int> closest = printKClosest(arr, k, x);

    cout << "The " << k << " closest elements to " << x << " are: ";
    for(int num : closest)
        cout << num << " ";
    cout << endl;

    return 0;
}