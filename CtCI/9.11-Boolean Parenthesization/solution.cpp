class Solution {
public:
    /**
     * @param symb: the array of symbols
     * @param oper: the array of operators
     * @return: the number of ways
     */
    int countParenth(string &symb, string &oper) {
        // write your code here
        int n = symb.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, 0)));
        for(int i = 0; i < n; i++) {
            if(symb[i] == 'T')
                dp[i][i][1] = 1;
            else
                dp[i][i][0] = 1;
        }
        for(int len = 2; len <= n; len++) {
            for(int i = 0; i + len <= n; i++) {
                int j = i + len - 1;
                for(int k = i; k < j; k++) {
                    // Split at k
                    // dp[i][k] ~ dp[k+1][j]
                    if(oper[k] == '&') {
                        dp[i][j][1] += dp[i][k][1] * dp[k+1][j][1];  // T && T
                        dp[i][j][0] += dp[i][k][0] * dp[k+1][j][1];  // F && T
                        dp[i][j][0] += dp[i][k][1] * dp[k+1][j][0];  // T && F
                        dp[i][j][0] += dp[i][k][0] * dp[k+1][j][0];  // F && F
                    } else if(oper[k] == '|') {
                        dp[i][j][0] += dp[i][k][0] * dp[k+1][j][0];  // F || F
                        dp[i][j][1] += dp[i][k][0] * dp[k+1][j][1];  // F || T
                        dp[i][j][1] += dp[i][k][1] * dp[k+1][j][0];  // T || F
                        dp[i][j][1] += dp[i][k][1] * dp[k+1][j][1];  // T || T
                    } else {
                        dp[i][j][0] += dp[i][k][1] * dp[k+1][j][1];  // T ^ T
                        dp[i][j][0] += dp[i][k][0] * dp[k+1][j][0];  // F ^ F
                        dp[i][j][1] += dp[i][k][0] * dp[k+1][j][1];  // F ^ T
                        dp[i][j][1] += dp[i][k][1] * dp[k+1][j][0];  // T ^ F
                    }
                }
            }
        }
        return dp[0][n-1][1];
    }
};
