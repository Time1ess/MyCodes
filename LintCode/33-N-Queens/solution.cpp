class Solution {
public:
    /*
     * @param n: The number of queens
     * @return: All distinct solutions
     */
    vector<string> make_board(int n)
    {
        vector<string> ans;
        for(int i = 1; i <= n; i++)
            ans.push_back(string(n, '.'));
        return ans;
    }
    bool valid(vector<string> &board, int n, int x, int y)
    {
        for(int i = 0; i < x; i++)
            if(board[i][y] == 'Q')
                return false;
        for(int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--)
            if(board[i][j] == 'Q')
                return false;
        for(int i = x - 1, j = y + 1; i >= 0 && j < n; i--, j++)
            if(board[i][j] == 'Q')
                return false;
        return true;
    }
    void generate_solutions(vector<vector<string>> &ans, vector<string> &board,
                            int x, int n)
    {
        if(x == n)
        {
            ans.push_back(board);
            return;
        }
        for(int y = 0; y < n; y++)
            if(valid(board, n, x, y))
            {
                board[x][y] = 'Q';
                generate_solutions(ans, board, x + 1, n);
                board[x][y] = '.';
            }
    }
    vector<vector<string>> solveNQueens(int n) {
        // write your code here
        vector<vector<string>> ans;
        vector<string> board = make_board(n);
        generate_solutions(ans, board, 0, n);
        return ans;
    }
};
