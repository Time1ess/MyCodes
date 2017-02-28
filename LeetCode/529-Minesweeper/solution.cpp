// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-28 13:13
// Last modified: 2017-02-28 13:13
// Filename: solution.cpp
// Description:
class Solution {
public:
    void dfs(vector<vector<char>>& board, int sizex, int sizey, int x, int y)
    {
        queue<pair<int, int>> q;
        pair<int, int> p;
        if(board[x][y] != 'E')
            return;
        char ch;
        int minx = max(x-1, 0);
        int maxx = min(x+1, sizex-1);
        int miny = max(y-1, 0);
        int maxy = min(y+1, sizey-1);
        int mine_cnt = 0;
        int sub_cnt = 0;
        for(int i=minx; i <= maxx; i++)
            for(int j=miny; j <= maxy; j++)
            {
                if(i == x && j == y)
                    continue;
                else
                {
                    ch = board[i][j];
                    if(ch == 'M')
                        mine_cnt ++;
                    if(ch == 'E')
                    {
                        board[x][y] = 'N';
                        q.push(make_pair(i, j));
                    }
                }
            }
        if(mine_cnt)
            board[x][y] = '0' + mine_cnt;
        else
            board[x][y] = 'B';
        if(board[x][y] == 'B')
            while(!q.empty())
            {
                p = q.front();
                q.pop();
                dfs(board, sizex, sizey, p.first, p.second);
            }
    }
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        int sizex = board.size();
        int sizey = board[0].size();
        int mine_cnt = 0;
        int x = click[0];
        int y = click[1];
        if(board[x][y] == 'M')
            board[x][y] = 'X';
        else
            dfs(board, sizex, sizey, click[0], click[1]);
        return board;
    }
};
