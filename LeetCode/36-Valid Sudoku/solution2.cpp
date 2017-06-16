// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-16 11:00
// Last modified: 2017-06-16 11:00
// Filename: solution2.cpp
// Description:
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bool block[9][9]={{0}}, row[9][9]={{0}}, col[9][9]={{0}};
        int bnum, num;
        for(int i = 0; i < board.size(); i++)
        {
            for(int j = 0; j < board[i].size(); j++)
            {
                if(board[i][j] == '.')
                    continue;
                num = board[i][j] - '1';
                bnum = i / 3 * 3 + j / 3;
                if(row[i][num] || col[j][num] || block[bnum][num])
                    return false;
                row[i][num] = col[j][num] = block[bnum][num] = true;
            }
        }
        return true;
    }
};
