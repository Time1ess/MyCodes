class Solution {
public:
    bool search_word(vector<vector<char>>& board, string& word, int idx, int len, int x, int y, int m, int n) {
        if (idx == len) {
            return true;
        }
        if (x < 0 || x == m || y < 0 || y == n || board[x][y] == ' ' || board[x][y] != word[idx]) {
            return false;
        }
        char tmp = board[x][y];
        board[x][y] = ' ';
        bool found = false;
        found = found || search_word(board, word, idx + 1, len, x - 1, y, m, n);
        found = found || search_word(board, word, idx + 1, len, x + 1, y, m, n);
        found = found || search_word(board, word, idx + 1, len, x, y - 1, m, n);
        found = found || search_word(board, word, idx + 1, len, x, y + 1, m, n);
        board[x][y] = tmp;
        return found;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        if (m == 0) {
            return false;
        }
        int n = board[0].size();
        if (n == 0) {
            return false;
        }
        int len = word.length();
        for (int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if (search_word(board, word, 0, len, i, j, m, n)) {
                    return true;
                }
            }
        }
        return false;
    }
};
