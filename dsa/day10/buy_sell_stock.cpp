#include <bits/stdc++.h>
using namespace std;

int maxProfit(vector<int>& prices)
{
    int currentMaxProfit = 0;
    int minIndex = 0, maxIndex = 0;

    if(prices.size() <= 1)
        return 0;

    int currentIndex = 0;
    for(int num : prices)
    {
        if(num < prices[minIndex])
        {
            minIndex = currentIndex;
            maxIndex = minIndex;
        }
        else if((num >= prices[maxIndex]))
        {
            maxIndex = currentIndex;
            int currentProfit = (prices[maxIndex] - prices[minIndex]); 
            currentMaxProfit =  (currentProfit > currentMaxProfit)? currentProfit : currentMaxProfit;
        }

        currentIndex++;
    }

    return currentMaxProfit;
}

int main()
{
    vector<int> arr = {7, 1, 5, 3, 6, 4};

    int bestProfit = maxProfit(arr);

    cout << bestProfit << endl;
}