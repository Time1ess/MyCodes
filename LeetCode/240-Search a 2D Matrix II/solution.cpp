// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-31 14:44
// Last modified: 2017-03-31 14:44
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool binary(vector<vector<int>> &matrix, int rs, int re, int cs, int ce, int target)
    {
        if(rs > re || cs > ce)
            return false;
        int rm = (rs + re)>>1, cm = (cs + ce)>>1;
        if(matrix[rm][cm] == target)
            return true;
        else if(matrix[rm][cm] > target)
            return binary(matrix, rs, re, cs, cm-1, target) || binary(matrix, rs, rm-1, cm, ce, target);
        else
            return binary(matrix, rs, re, cm+1, ce, target) || binary(matrix, rm+1, re, cs, cm, target);
    }
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if(m == 0)
            return false;
        int n = matrix[0].size();
        return binary(matrix, 0, m-1, 0, n-1, target);
    }
};
