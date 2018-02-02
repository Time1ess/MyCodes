class Solution {
public:
    /**
     * @param s: A string 
     * @param p: A string includes "." and "*"
     * @return: A boolean
     */
    bool memo_dfs(const string &s, const string &p,
                  vector<vector<bool>> &visited,
                  vector<vector<bool>> &res,
                  const int &len_s, const int &len_p,
                  int i, int j)
    {
        if(visited[i][j])
            return res[i][j];
        bool match = false;
        if(j == len_p)
            match = i == len_s;
        else
        {
            bool first_match = (i < len_s && (s[i] == p[j] || p[j] == '.'));
            if(j+1 < len_p && p[j+1] == '*')
                // ignore x*(by j+2) or match a char(by i+1)
                match = memo_dfs(s, p, visited, res, len_s, len_p, i, j+2)
                    || (first_match && memo_dfs(s, p, visited, res, len_s, len_p, i+1, j));
            else
                match = first_match && memo_dfs(s, p, visited, res, len_s, len_p, i+1, j+1);
        }
        res[i][j] = match;
        visited[i][j] = true;
        return match;
    }
    bool isMatch(string s, string p) {
        // write your code here
        int len_s = s.length(), len_p = p.length();
        vector<vector<bool>> visited(len_s+1, vector<bool>(len_p+1, false));
        vector<vector<bool>> res(len_s+1, vector<bool>(len_p+1, false));
        return memo_dfs(s, p, visited, res, len_s, len_p, 0, 0);
    }
};
