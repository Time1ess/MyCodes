// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-11 08:54
// Last modified: 2017-05-11 08:54
// Filename: solution.cpp
// Description:
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int height = matrix.size();
        if(height == 0)
            return;
        int width = matrix[0].size();
        int last_zero_row = -1;
        for(int r = height - 1; r >= 0; r--)
        {
            for(int c = 0; c < width; c++)
            {
                if(matrix[r][c] == 0)
                {
                    last_zero_row = r;
                    break;
                }
            }
            if(last_zero_row != -1)
                break;
        }
        if(last_zero_row == -1)
            return;
        for(int r = 0; r < last_zero_row; r++)
        {
            bool has_zero = false;
            for(int c = 0; c < width; c++)
            {
                if(matrix[r][c] == 0)
                {
                    has_zero = true;
                    matrix[last_zero_row][c] = 0;
                }
            }
            if(has_zero)
                for(int c = 0; c < width; c++)
                    matrix[r][c] = 0;
        }
        for(int c = 0; c < width; c++)
        {
            if(matrix[last_zero_row][c] == 0)
                for(int r = 0; r < height; r++)
                    matrix[r][c] = 0;
        }
        for(int c = 0; c < width; c++)
            matrix[last_zero_row][c] = 0;
    }
};
