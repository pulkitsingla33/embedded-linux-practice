#include <bits/stdc++.h>
using namespace std;

vector<int> asteroidCollision(vector<int>& asteroids)
{
    stack<int> st;
    for(int i = 0; i < asteroids.size(); i++)
    {
        int is_equal = 0;
        if(asteroids[i] < 0)
        {
            while(!st.empty() && (asteroids[st.top()] > 0))
            {
                if(abs(asteroids[i]) >= asteroids[st.top()])
                {
                    if(abs(asteroids[i]) == asteroids[st.top()])
                    {
                        is_equal = 1;
                        st.pop();
                        break;
                    }

                    st.pop();
                }
                else
                {
                    break;
                }
            }
            if(st.empty() || (asteroids[st.top()] < 0))
            {
                if(!is_equal)
                    st.push(i);
            }
        }
        else
        {
            st.push(i);
        }
    }

    deque<int> my_deque;
    while(!st.empty())
    {
        my_deque.push_front(asteroids[st.top()]);
        st.pop();
    }

    vector<int> result(my_deque.begin(), my_deque.end());

    return result;
}

int main()
{
    vector<int> asteroids = {-2,1,1,-1};
    vector<int> output = asteroidCollision(asteroids);

    for(int num: output)
    {
        cout << num << " ";
    }
    cout << endl;


    return 0;
}