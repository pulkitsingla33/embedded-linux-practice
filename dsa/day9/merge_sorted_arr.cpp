#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> arr1 = {1, 3, 5, 7, 0, 0, 0};
    vector<int> arr2 = {2, 5, 6};

    int m = 4;
    int n = 3;

    int p1 = m - 1;
    int p2 = n - 1;
    int p = m + n - 1;

    while(p1 >= 0 && p2 >= 0)
    {
        if(arr1[p1] > arr2[p2])
        {
            arr1[p] = arr1[p1];
            p1--;
        }
        else
        {
            arr1[p] = arr2[p2];
            p2--;
        }
        p--;
    }

    while(p2 >= 0)
    {
        arr1[p] = arr2[p2];
        p2--;
        p--;
    }

    for(int i : arr1)
    {
        cout << i << " ";
    }

    cout << endl;

    return 0;
}