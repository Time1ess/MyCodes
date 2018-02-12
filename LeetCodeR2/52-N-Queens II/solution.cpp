class Solution {
public:
    bool is_valid(vector<pair<int, int>> &queens, int x, int y)
    {
        for(auto q: queens)
            if(q.second == y || abs(q.first - x) == abs(q.second - y))
                return false;
        return true;
    }
    void backtrack(int &ans, vector<pair<int, int>> &queens, int idx, int n)
    {
        if(idx == n)
        {
            ans++;
            return;
        }
        for(int y = 0; y < n; y++)  // (idx, y)
        {
            if(!is_valid(queens, idx, y))
                continue;
            queens.push_back({idx, y});
            backtrack(ans, queens, idx+1, n);
            queens.pop_back();
        }
    }
    int totalNQueens(int n) {
        int ans = 0;
        vector<pair<int, int>> queens;
        backtrack(ans, queens, 0, n);
        return ans;
    }
};
