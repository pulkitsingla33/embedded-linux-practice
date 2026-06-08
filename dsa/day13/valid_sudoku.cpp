#include <bits/stdc++.h>
using namespace std;

bool isValidSudoku(vector<vector<char>>& board)
{
    unordered_set<char> numbers;
    for(vector<char> row: board)
    {
        for(char num: row)
        {
            if(num == '.')
                continue;
            else if(num >= '0' && num <= '9')
            {
                if(numbers.count(num))
                    return false;
                else
                    numbers.insert(num);
            }
        }
        numbers.clear();
    }

    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            char num = board[j][i];

            if(num == '.')
                continue;
            else if(num >= '0' && num <= '9')
            {
                if(numbers.count(num))
                    return false;
                else
                    numbers.insert(num);
            }
        }
        numbers.clear();
    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int m = 0; m < 3; m++)
            {
                for(int n = 0; n < 3; n++)
                {
                    char num = board[(i*3) + m][(j * 3) + n];

                    if(num == '.')
                        continue;
                    else if(num >= '0' && num <= '9')
                    {
                        if(numbers.count(num))
                            return false;
                        else
                            numbers.insert(num);
                    }
                }
            }
            numbers.clear();
        }
    }

    return true;
}

int main()
{

    vector<vector<char>> myBoard = {
        {'8', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };

    cout << isValidSudoku(myBoard) << endl;
    return 0;
}