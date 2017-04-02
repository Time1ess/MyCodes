// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-02 10:10
// Last modified: 2017-04-02 10:10
// Filename: solution.cpp
// Description:
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if(n == 0 || matrix[0].size() == 0)
            return;
        //transpose
        int i, k;
        for(k = 0; k < n; k++)
        {
            i = k;
            while(i < n)
            {
                swap(matrix[k][i], matrix[i][k]);
                i++;
            }
        }
        //column reverse
        for(int k = 0; k < n / 2; k++)
        {
            for(i = 0; i < n; i++)
                swap(matrix[i][k], matrix[i][n - 1 - k]);
        }
    }
};
