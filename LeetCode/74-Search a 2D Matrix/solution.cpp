// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-06 14:54
// Last modified: 2017-06-06 14:54
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool search(vector<vector<int>> &matrix, int target, int t, int b, int l, int r)
    {
        if(t >= b - 1 && l >= r)
            return false;
        if(t < b - 1)
        {
            int m = t + (b - t) / 2;
            if(matrix[m][0] == target)
                return true;
            else if(matrix[m][0] < target)
                return search(matrix, target, m, b, l, r);
            else
                return search(matrix, target, t, m, l, r);
        }
        else
        {
            int m = l + (r - l) / 2;
            if(matrix[t][m] == target)
                return true;
            else if(matrix[t][m] < target)
                return search(matrix, target, t, b, m+1, r);
            else
                return search(matrix, target, t, b, l, m);
        }
    }
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row = matrix.size();
        if(row == 0)
            return false;
        int col = matrix[0].size();
        if(col == 0)
            return false;
        return search(matrix, target, 0, row, 0, col);
    }
};
