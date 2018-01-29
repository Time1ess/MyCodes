class Solution {
public:
    /*
     * @param symb: the array of symbols
     * @param oper: the array of operators
     * @return: the number of ways
     */
    int countParenth(string &symb, string &oper) {
        // write your code here
        int n = symb.length();
        int m = oper.length();
        int ***dp = new int**[n + 1];
        for(int i = 0; i < n + 1; i++)
        {
            dp[i] = new int*[n + 1];
            for(int j = 0; j < n + 1; j++)
            {
                dp[i][j] = new int[2];
                dp[i][j][0] = dp[i][j][1] = 0;
            }
        }
        for(int i = 0; i < n; i++)
        {
            dp[i][i+1][0] = symb[i] == 'T' ? 0 : 1;
            dp[i][i+1][1] = symb[i] == 'T' ? 1 : 0;
        }
        for(int len = 2; len <= n; len++)
        {
            for(int i = 0; i+len <= n; i++)
            {
                int j = i + len;
                dp[i][j][0] = dp[i][j][1] = 0;
                for(int k = i + 1; k < j; k++)
                {
                    // Split at k
                    if(oper[k-1] == '^')
                    {
                        dp[i][j][0] += dp[i][k][0] * dp[k][j][0];
                        dp[i][j][0] += dp[i][k][1] * dp[k][j][1];
                        dp[i][j][1] += dp[i][k][0] * dp[k][j][1];
                        dp[i][j][1] += dp[i][k][1] * dp[k][j][0];
                    }
                    else if(oper[k-1] == '&')
                    {
                        dp[i][j][0] += dp[i][k][0] * (dp[k][j][0] + dp[k][j][1]);
                        dp[i][j][0] += dp[i][k][1] * dp[k][j][0];
                        dp[i][j][1] += dp[i][k][1] * dp[k][j][1];
                    }
                    else
                    {
                        dp[i][j][0] += dp[i][k][0] * dp[k][j][0];
                        dp[i][j][1] += dp[i][k][1] * (dp[k][j][0] + dp[k][j][1]);
                        dp[i][j][1] += dp[i][k][0] * dp[k][j][1];
                    }
                }
            }
        }
        int ans = dp[0][n][1];
        for(int i = 0; i < n + 1; i++)
        {
            for(int j = 0; j < n + 1; j++)
                delete[] dp[i][j];
            delete[] dp[i];
        }
        delete[] dp;
        return ans;
    }
};
