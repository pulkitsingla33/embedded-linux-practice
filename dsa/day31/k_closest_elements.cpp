#include <bits/stdc++.h>
using namespace std;

vector<int> findClosestElements(vector<int>& arr, int k, int x)
{
    int first = 0, last = arr.size() - 1;
    int targetFound = 0;
    int lowerIndex = 0, higherIndex = 0;
    while(first <= last)
    {
        int mid = (first + last)/2;
        if(arr[mid] == x)
        {
            targetFound = 1;
            lowerIndex = mid;
            break;
        }
        else if(arr[mid] > x)
        {
            last = mid - 1;
        }
        else
        {
            first = mid + 1;
        }
    }

    if(!targetFound)
    lowerIndex = last;
    
    vector<int> closest_elements(k);
    higherIndex = lowerIndex + 1;

    while((lowerIndex >= 0) && (higherIndex <= (arr.size() - 1) && (k > 0)))
    {
        if(abs(arr[lowerIndex] - x) <= abs(arr[higherIndex] - x))
        {
            lowerIndex--;
        }
        else
        {
            higherIndex++;
        }
        k--;
    }

    while(k > 0)
    {
        if(lowerIndex >= 0)
        {
            lowerIndex--;
        }
        else if(higherIndex <= (arr.size() - 1))
        {
            higherIndex++;
        }
        k--;
    }

    for(int i = lowerIndex + 1; i < higherIndex; i++)
    {
        closest_elements[i - (lowerIndex + 1)] = arr[i];
    }
    
    return closest_elements;
}

int main()
{
    vector<int> arr = {1,2,3,4,5};
    int k = 4, x = 3;

    vector<int> closest_elements = findClosestElements(arr, k, x);

    for(int num: closest_elements)
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}