// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-24 10:03
// Last modified: 2017-04-24 10:03
// Filename: solution.cpp
// Description:
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size();
        if(m == 0)
            return;
        int n = board[0].size();
        int cnt;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
            {
                cnt = 0;
                for(int ti = max(0, i-1); ti <= min(m-1, i+1); ti++)
                    for(int tj = max(0, j-1); tj <= min(n-1, j+1); tj++)
                        cnt += board[ti][tj] & 1;
                cnt -= board[i][j] & 1;
                if((1 & board[i][j]) == 0 && cnt == 3)
                    board[i][j] |= 1 << 1;
                else if((1 & board[i][j]) == 1 && (cnt == 2 || cnt == 3))
                    board[i][j] |= 1 << 1;
            }
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                board[i][j] >>= 1;
    }
};
