// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-16 10:55
// Last modified: 2017-06-16 10:55
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        map<int, map<char, bool>> bmap, rmap, cmap;
        int block;
        char num;
        for(int i = 0; i < board.size(); i++)
        {
            for(int j = 0; j < board[i].size(); j++)
            {
                if(board[i][j] == '.')
                    continue;
                num = board[i][j];
                block = i / 3 * 3 + j / 3;
                if(bmap[block][num] != false)
                    return false;
                else
                    bmap[block][num] = true;
                if(rmap[i][num] != false)
                    return false;
                else
                    rmap[i][num] = true;
                if(cmap[j][num] != false)
                    return false;
                else
                    cmap[j][num] = true;
            }
        }
        return true;
    }
};
