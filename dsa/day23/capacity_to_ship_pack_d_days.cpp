#include <bits/stdc++.h>
using namespace std;

int shipWithinDays(vector<int>& weights, int days)
{
    int min_capacity = *max_element(weights.begin(), weights.end());
    int result = 0;

    int first = min_capacity;
    int last = accumulate(weights.begin(), weights.end(), 0);

    while(first <= last)
    {
        int mid = (first + last)/2;
        int current_days = 1;
        int sum = 0;
        for(int num: weights)
        {
            if(sum + num > mid)
            {
                sum = num;
                current_days++;
            }
            else
            {
                sum += num;
            }
        }

        if(current_days <= days)
        {
            result = mid;
            last = mid - 1;
        }
        else if(current_days > days)
        {
            first = mid + 1;
        }
    }

    // if(result == 0)
    //     result = min_capacity;

    return result;
}

int main()
{
    vector<int> weights = {1,2,3,1,1};
    int days = 4;

    cout << "Ship Capacity is: " << shipWithinDays(weights, days) << endl;

    return 0;
}