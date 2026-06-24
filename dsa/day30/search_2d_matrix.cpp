#include <bits/stdc++.h>
using namespace std;

bool searchMatrix(vector<vector<int>>& matrix, int target)
{
    int M = matrix.size();
    int N = matrix[0].size();

    int first = 0, last = M - 1;
    int target_row = 0;
    while(first <= last)
    {
        int mid = (first + last)/2;
        if((target >= matrix[mid][0]) && (target <= matrix[mid][N-1]))
        {
            target_row = mid;
            break;
        }
        else if(target > matrix[mid][N-1])
        {
            first = mid + 1;
        }
        else if(target < matrix[mid][0])
        {
            last = mid - 1;
        }
    }


    first = 0, last = N -1;
    while(first <= last)
    {
        int mid = (first + last)/2;
        if(matrix[target_row][mid] == target)
        {
            return true;
        }
        else if(matrix[target_row][mid] > target)
        {
            last = mid - 1;
        }
        else if(matrix[target_row][mid] < target)
        {
            first = mid + 1;
        }
    }

    return false;
}

int main()
{
    vector<vector<int>> matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    int target = 13;
    
    cout << searchMatrix(matrix, target) << endl;

    return 0;
}