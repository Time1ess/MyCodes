class Solution {
public:
    int smoothed_value(vector<vector<int>> &M, int i, int j, int m, int n)
    {
        int s = 0;
        int c = 0;
        for(int x = max(0, i - 1); x < min(m, i + 2); x++)
            for(int y = max(0, j - 1); y < min(n, j + 2); y++)
            {
                s += M[x][y];
                c++;
            }
        return s / c;
    }
    vector<vector<int>> imageSmoother(vector<vector<int>>& M) {
        int m = M.size();
        int n = M[0].size();
        vector<vector<int>> ans(m, vector<int>(n, 0));
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                ans[i][j] = smoothed_value(M, i, j, m, n);
        return ans;
    }
};
