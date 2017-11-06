class Solution {
public:
    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        bool stable = false;
        int row = board.size(), col = board[0].size();
        int directions[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
        while(!stable)
        {
            stable = true;
            vector<vector<int>> new_board(board);
            for(int i = row - 1; i >= 0; i--)
            {
                // For every position
                for(int j = 0; j < col; j++)
                {
                    if(board[i][j] == 0)
                        continue;
                    bool crush = false;
                    // Search each direction
                    for(auto direction: directions)
                    {
                        int ti = i, tj = j;
                        while(ti >= 0 && ti < row && tj >= 0 && tj < col && board[ti][tj] == board[i][j])
                        {
                            ti += direction[0];
                            tj += direction[1];
                        }
                        int cnt = abs(i - ti) + abs(j - tj);
                        // Three or more are adjacent
                        if(cnt >= 3)
                        {
                            stable = false;
                            // Crush all except self
                            int ki = i + direction[0], kj = j + direction[1];
                            while(ki != ti || kj != tj)
                            {
                                new_board[ki][kj] = 0;
                                ki += direction[0];
                                kj += direction[1];
                            }
                            new_board[i][j] = 0;
                        }
                    }
                }
            }
            board = new_board;
            // Drop all candies
            for(int j = 0; j < col; j++)
            {
                int dst = row - 1, src = row - 1;
                while(dst >= 0 && src >= 0)
                {
                    while(dst > 0 && board[dst][j] != 0)
                        dst--;
                    if(dst == 0)
                        break;
                    src = dst - 1;
                    while(src >= 0 && board[src][j] == 0)
                        src--;
                    if(src < 0)
                        break;
                    board[dst][j] = board[src][j];
                    board[src][j] = 0;
                    dst--;
                }
            }
        }
        return board;
    }
};
