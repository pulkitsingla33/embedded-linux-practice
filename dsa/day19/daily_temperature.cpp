#include <bits/stdc++.h>
using namespace std;

vector<int> dailyTemperatures(vector<int>& temperatures)
{
    int arr_size = temperatures.size();
    stack<int> st;
    vector<int> answer(arr_size, 0);

    for(int i = arr_size - 1; i >= 0; i--)
    {
        if(st.empty())
        {
            st.push(i);
            continue;
        }

        while(!(st.empty()) && (temperatures[i] >= temperatures[st.top()]))
        {
            st.pop();
        }

        if(!st.empty())
            answer[i] = st.top() - i;
        
        st.push(i);
        
    }

    return answer;
}

int main()
{
    vector<int> temperatures = {73,74,75,71,69,72,76,73};

    vector<int> answer = dailyTemperatures(temperatures);

    for(int num: answer)
        cout << num << " ";

    cout << endl;


    return 0;
}