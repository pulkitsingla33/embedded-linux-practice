#include <bits/stdc++.h>
using namespace std;

bool dfs(int node, vector<vector<int>> &adj, vector<int> &visited)
{
    //mark as visiting
    visited[node] = 1;

    for(int neighbor: adj[node])
    {
        if(visited[neighbor] == 1)
            return false;
        else if(visited[neighbor] == 0)
        {
            if(!dfs(neighbor, adj, visited))
                return false;
        }
    }

    visited[node] = 2;
    return true;
}

bool canFinish(int n, vector<vector<int>>& prerequisites)
{
    vector<vector<int>> adj(n);
    for (auto& pre : prerequisites)
    {
        int dest = pre[0];
        int src = pre[1];
        adj[src].push_back(dest);
    }
    // 0 = unvisited, 1 = visiting, 2 = visited
    vector<int> visited(n, 0); 

    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {
            if (!dfs(i, adj, visited))
            {
                // cycle detected
                return false; 
            }
        }
    }
    
    return true;
}

int main()
{
    int n = 4;
    vector<vector<int>> prerequisites = { {2, 0}, {2, 1}, {3, 2} };

    cout << (canFinish(n, prerequisites) ? "true" : "false") << endl;

    return 0;
}