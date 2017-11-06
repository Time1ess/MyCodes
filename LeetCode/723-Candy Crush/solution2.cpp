class Solution {
public:
    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        int row = board.size(), col = board[0].size();
        while(true)
        {
            vector<pair<int, int>> crushes;
            for(int i = row - 1; i >= 0; i--)
                for(int j = 0; j < col; j++)
                    if(board[i][j])
                    {
                        int t = i, b = i, l = j, r = j;
                        while(t >= 0 && t > i - 3 && board[t][j] == board[i][j]) t--;
                        while(b < row && b < i + 3 && board[b][j] == board[i][j]) b++;
                        while(r < col && r < j + 3 && board[i][r] == board[i][j]) r++;
                        while(l >= 0 && l > j - 3 && board[i][l] == board[i][j]) l--;
                        if(b - t > 3 || r - l > 3)
                            crushes.push_back(make_pair(i, j));
                    }
            if(crushes.empty())
                break;
            for(auto x: crushes)
                board[x.first][x.second] = 0;
            for(int j = 0; j < col; j++)
            {
                int dst = row - 1;
                for(int src = row - 1; src >= 0; src--)
                    if(board[src][j])
                        swap(board[src][j], board[dst--][j]);
                while(dst >= 0)
                    board[dst--][j] = 0;
            }
        }
        return board;
    }
};
