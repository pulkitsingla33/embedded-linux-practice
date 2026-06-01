#include <bits/stdc++.h>
using namespace std;

bool isValidParantheses(string str)
{
    stack<char> brackets;    

    int i = 0;
    while(str[i])
    {
        char c = str[i];
        if(c == '(' || c == '{' || c == '[')
            brackets.push(c);
        else if(c == ')')
        {
            if((!brackets.empty()) && (brackets.top() == '('))
                brackets.pop();
            else
                return false;                
        }
        else if(c == ']')
        {
            if((!brackets.empty()) && (brackets.top() == '['))
                brackets.pop();
            else
                return false;
        }
        else if(c == '}')
        {
            if((!brackets.empty()) && (brackets.top() == '{'))
                brackets.pop();
            else
                return false;
        }
        i++;
    }

    if(brackets.empty() && str.length())
        return true;

    return false;
}



int main()
{
    string s= "]";

    cout << isValidParantheses(s) << endl;
    
    return 0;
}