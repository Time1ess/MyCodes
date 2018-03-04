class Solution {
public:
    bool found(vector<vector<char>> &board, vector<vector<bool>> &visited, string &word, int n, int m, int i, int j, int idx)
    {
        if(idx == word.length())
            return true;
        if(i < 0 || i == n || j < 0 || j == m || visited[i][j] || board[i][j] != word[idx])
            return false;
        bool ans = false;
        visited[i][j] = true;
        ans = ans || found(board, visited, word, n, m, i-1, j, idx+1);
        ans = ans || found(board, visited, word, n, m, i+1, j, idx+1);
        ans = ans || found(board, visited, word, n, m, i, j-1, idx+1);
        ans = ans || found(board, visited, word, n, m, i, j+1, idx+1);
        visited[i][j] = false;
        return ans;
    }
    bool exist(vector<vector<char>>& board, string word) {
        if(word.length() == 0)
            return true;
        int n = board.size();
        if(n == 0)
            return false;
        int m = board[0].size();
        if(m == 0)
            return false;
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                if(found(board, visited, word, n, m, i, j, 0))
                    return true;
        return false;
    }
};
