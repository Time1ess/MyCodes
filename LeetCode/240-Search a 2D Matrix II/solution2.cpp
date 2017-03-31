// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-31 14:50
// Last modified: 2017-03-31 14:50
// Filename: solution2.cpp
// Description:
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if(m == 0)
            return false;
        int i = 0, j = matrix[0].size() - 1;
        while(i < m && j >= 0)
        {
            if(matrix[i][j] == target)
                return true;
            else if(matrix[i][j] < target)
                i++;
            else
                j--;
        }
        return false;
    }
};
