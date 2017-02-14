// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-14 09:18
// Last modified: 2017-02-14 09:18
// Filename: solution.cpp
// Description:
class Solution {
public:
    void traverse(vector<vector<int>> &matrix, int x, int y, int direction, int m, int n, vector<int> &result)
    {
        // direction
        //      0: Bottom left -> Up right
        //      1: Up right -> Bottom left
        if(x >= m || y >= n || x < 0 || y < 0)
            return;
        if(direction == 0)
        {
            for(; x >= 0 && y < n; x--, y++)
                result.push_back(matrix[x][y]);
            x++;y--;
            if(y == n-1)
                x++;
            else
                y++;
            traverse(matrix, x, y, 1, m, n, result);
        }
        else
        {
            for(; x < m && y >= 0; x++, y--)
                result.push_back(matrix[x][y]);
            x--;y++;
            if(x == m-1)
                y++;
            else
                x++;
            traverse(matrix, x, y, 0, m, n, result);
        }
    }
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        int m, n;
        vector<int> result;
        m = matrix.size();
        if(m == 0)
            return result;
        n = matrix[0].size();
        traverse(matrix, 0, 0, 0, m, n, result);
        return result;
    }
};
