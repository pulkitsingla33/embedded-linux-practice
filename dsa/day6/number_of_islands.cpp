#include <bits/stdc++.h>
using namespace std;

bool isSafe(vector<vector<char>>& grid, int row, int col, vector<vector<bool>>& visited)
{
    return (row >= 0) && (row < grid.size()) && (col >= 0) && (col < grid[0].size()) && (grid[row][col] == '1' && !visited[row][col]);
}

void dfs(vector<vector<char>>& grid, int row, int col, vector<vector<bool>>& visited)
{
    static int rowNum[] = {-1, 0, 0, 1};
    static int colNum[] = {0, -1, 1, 0};

    visited[row][col] = true;

    for(int k = 0; k < 4; k++)
    {
        if(isSafe(grid, row + rowNum[k], col + colNum[k], visited))
            dfs(grid, row + rowNum[k], col + colNum[k], visited);
    }
}

int numIslands(vector<vector<char>>& grid)
{
    int count = 0;
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[0].size(); j++)
        {
            if(grid[i][j] == '1' && !visited[i][j])
            {
                dfs(grid, i, j, visited);
                count++;
            }
        }
    }
    return count;
}

int main()
{
    vector<vector<char>> grid = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };

    cout << "Number of islands: " << numIslands(grid) << endl;
    return 0;
}