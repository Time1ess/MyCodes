// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-18 14:28
// Last modified: 2016-10-18 14:28
// Filename: solution.cpp
// Description:
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        int cnt = 0;
        int t;
        for(int i=0; i < board.size(); i++)
            for(int j=0; j < board[i].size(); j++)
            {
                if(board[i][j] == 'X')
                {
                    cnt++;
                    while((++j) < board[i].size() && board[i][j] == 'X');
                }
            }
        for(int j=0; j < board[0].size(); j++)
            for(int i=0; i < board.size(); i++)
            {
                t = 0;
                while(board[i][j] == 'X')
                {
                    t++;
                    i++;
                    if(i >= board.size())
                        break;
                }
                if(t)
                    cnt -= t-1;
            }
        return cnt;
    }
};
