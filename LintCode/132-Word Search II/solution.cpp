class TrieNode {
public:
    TrieNode() {
        end = false;
        for(int i = 0; i < 26; i++)
            next[i] = NULL;
    }
    void add_word(const string &word) {
        TrieNode *node = this;
        for(auto ch: word) {
            if(node->next[ch-'a'] == NULL)
                node->next[ch-'a'] = new TrieNode();
            node = node->next[ch-'a'];
        }
        node->end = true;
    }
    bool end;
    TrieNode* next[26];
};

class Solution {
public:
    /**
     * @param board: A list of lists of character
     * @param words: A list of string
     * @return: A list of string
     */
    void search(vector<string> &ans, vector<vector<char>> &board,
           vector<vector<bool>> &visited, string &cur, const int &m, const int &n,
           int x, int y, TrieNode *node) {
        if (x < 0 || x >= m || y < 0 || y >= n || visited[x][y])
            return;
        if (node->end == true) {
            ans.push_back(cur);
            node->end = false;
        }
        visited[x][y] = true;
        static vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for(auto dir: dirs) {
            int nx = x + dir.first;
            int ny = y + dir.second;
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || visited[nx][ny])
                continue;
            if (node->next[board[nx][ny]-'a'] == NULL)
                continue;
            cur.push_back(board[nx][ny]);
            search(ans, board, visited, cur, m, n, nx, ny,
                   node->next[board[nx][ny] - 'a']);
            cur.pop_back();
        }
        visited[x][y] = false;
    }
    vector<string> wordSearchII(vector<vector<char>> &board, vector<string> &words) {
        // write your code here
        int m = board.size();
        if (m == 0)
            return {};
        int n = board[0].size();
        if (n == 0)
            return {};
        TrieNode* trie = new TrieNode();
        for(const string &word: words)
            trie->add_word(word);
        vector<string> ans;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        string cur;
        for(int i = 0; i < m; i ++) {
            for(int j = 0; j < n; j++) {
                if (trie->next[board[i][j]-'a'] != NULL) {
                    cur.push_back(board[i][j]);
                    search(ans, board, visited, cur, m, n, i, j,
                           trie->next[board[i][j]-'a']);
                    cur.pop_back();
                }
            }
        }
        return ans;
    }
};
