class Solution {
public:
    int count_mines(vector<vector<char>> &board, int m, int n, int x, int y)
    {
        int count = 0;
        for(int i = max(0, x - 1); i <= min(m - 1, x + 1); i++)
            for(int j = max(0, y - 1); j <= min(n - 1, y + 1); j++)
                if(!(i == x && j == y) && board[i][j] == 'M')
                    count++;
        return count;
    }
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        vector<vector<char>> new_board = board;
        int m = board.size();
        if(m == 0)
            return new_board;
        int n = board[0].size();
        if(n == 0)
            return new_board;
        if(board[click[0]][click[1]] == 'M')
        {
            new_board[click[0]][click[1]] = 'X';
            return new_board;
        }
        queue<vector<int>> q;
        q.push(click);
        while(!q.empty())
        {
            auto f = q.front();
            int x = f[0];
            int y = f[1];
            q.pop();
            if(x < 0 || x >= m || y < 0 || y >= n)
                continue;
            if(new_board[x][y] != 'E' && new_board[x][y] != 'M')
                continue;
            int mines = count_mines(board, m, n, x, y);
            if(mines == 0)
            {
                new_board[x][y] = 'B';
                for(int i = max(0, x - 1); i <= min(m - 1, x + 1); i++)
                    for(int j = max(0, y - 1); j <= min(n - 1, y + 1); j++)
                        if(!(i == x && j == y))
                            q.push({i, j});
            }
            else
                new_board[x][y] = mines + '0';
        }
        return new_board;
    }
};
