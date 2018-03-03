class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int n = matrix.size();
        if(n == 0)
            return 0;
        int m = matrix[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));
        dp[0][0] = matrix[0][0] == '1' ? 1 : 0;
        for(int i = 1; i < n; i++)
            dp[i][0] = dp[i-1][0] + (matrix[i][0] == '1' ? 1 : 0);
        for(int j = 1; j < m; j++)
            dp[0][j] = dp[0][j-1] + (matrix[0][j] == '1' ? 1 : 0);
        for(int i = 1; i < n; i++)
            for(int j = 1; j < m; j++)
                dp[i][j] = dp[i][j-1] + dp[i-1][j] - dp[i-1][j-1] + (matrix[i][j] == '1' ? 1 : 0);
        int ans = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                for(int k = 0; i + k < n && j + k < m; k++)
                {
                    if(matrix[i][j] != '1')
                        break;
                    int sum = dp[i+k][j+k];
                    if(j > 0)
                        sum -= dp[i+k][j-1];
                    if(i > 0)
                        sum -= dp[i-1][j+k];
                    if(i > 0 && j > 0)
                        sum += dp[i-1][j-1];
                    if(sum == (k+1) * (k+1))
                        ans = max(ans, sum);
                }
        return ans;
    }
};
