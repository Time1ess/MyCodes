// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-06 11:59
// Last modified: 2017-08-06 11:59
// Filename: solution.cpp
// Description:
class Solution {
public:
    void dfs(vector<vector<int>> &matrix, vector<vector<int>> &visited, vector<pair<int, int>> &ans, int i, int j, int pre, int preval)
    {
        if(i < 0 || i >= matrix.size() || j < 0 || j >= matrix[0].size() ||
           matrix[i][j] < pre || (visited[i][j] & preval) == preval)
            return;
        visited[i][j] |= preval;
        if(visited[i][j] == 3)
            ans.push_back(make_pair(i, j));
        dfs(matrix, visited, ans, i+1, j, matrix[i][j], visited[i][j]);
        dfs(matrix, visited, ans, i-1, j, matrix[i][j], visited[i][j]);
        dfs(matrix, visited, ans, i, j+1, matrix[i][j], visited[i][j]);
        dfs(matrix, visited, ans, i, j-1, matrix[i][j], visited[i][j]);        
    }
    vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
        vector<pair<int, int>> ans;
        if(matrix.size() == 0)
            return ans;
        int m = matrix.size(), n = matrix[0].size();
        
        vector<vector<int>> visited(m, vector<int>(n, 0));
        for(int i = 0; i < m; i++)
        {
            dfs(matrix, visited, ans, i, 0, INT_MIN, 1);
            dfs(matrix, visited, ans, i, n-1, INT_MIN, 2);
        }
        for(int i = 0; i < n; i++)
        {
            dfs(matrix, visited, ans, 0, i, INT_MIN, 1);
            dfs(matrix, visited, ans, m-1, i, INT_MIN, 2);
        }
        return ans;
    }
};
