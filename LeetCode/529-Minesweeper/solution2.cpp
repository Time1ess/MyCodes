// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-28 18:31
// Last modified: 2017-02-28 18:31
// Filename: solution2.cpp
// Description:
class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        queue<pair<int, int>> q;
        pair<int, int> p;
        int xmin, xmax, ymin, ymax, x, y;
        int cnt;
        int m = board.size();
        int n = board[0].size();
        if(board[click[0]][click[1]] == 'M')
            board[click[0]][click[1]] = 'X';
        else
        {
            q.push(make_pair(click[0], click[1]));
            while(!q.empty())
            {
                p = q.front();
                x = p.first;
                y = p.second;
                q.pop();
                if(board[x][y] != 'E')
                    continue;
                cnt = 0;
                xmin = max(0, x-1);
                xmax = min(m-1, x+1);
                ymin = max(0, y-1);
                ymax = min(n-1, y+1);
                for(int i=xmin; i <= xmax; i++)
                    for(int j=ymin; j <= ymax; j++)
                    {
                        if(i == x && j == y)
                            continue;
                        else if(board[i][j] == 'M')
                            cnt++;
                    }
                if(cnt == 0)
                {
                    board[x][y] = 'B';
                    for(int i=xmin; i <= xmax; i++)
                        for(int j=ymin; j <= ymax; j++)
                        {
                            if(i == x && j == y)
                                continue;
                            else
                                q.push(make_pair(i, j));
                        }
                }
                else
                    board[x][y] = '0' + cnt;
            }
        }
        return board;
    }
};
