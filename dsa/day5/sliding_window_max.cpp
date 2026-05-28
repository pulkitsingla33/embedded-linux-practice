#include <bits/stdc++.h>
using namespace std;

vector<int> maxofSubarrays(vector<int>& arr, int k)
{
    vector<int> res;
    deque<int> dq; // Will store indices of elements in the current window

    for(int i = 0; i<k; i++)
    {
        while(!dq.empty() && arr[i]>=arr[dq.back()])
            dq.pop_back();

        dq.push_back(i);
    }

    for(int i = k; i < arr.size(); i++)
    {
        res.push_back(arr[dq.front()]);
        while(!dq.empty() && dq.front() <= i-k)
        {
            dq.pop_front();
        }

        while(!dq.empty() && arr[i]>=arr[dq.back()])
            dq.pop_back();

        dq.push_back(i);
    }

    res.push_back(arr[dq.front()]);

    return res;
}

int main()
{
    vector<int> arr = {1,2,3,10,20,5,4,1};
    int k = 3;
    vector<int> res = maxofSubarrays(arr, k);
    for(int maxVal: res)
    {
        cout << maxVal << " ";
    }
    cout << endl;
    return 0;
}