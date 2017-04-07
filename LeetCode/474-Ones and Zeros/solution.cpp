// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-07 18:57
// Last modified: 2017-04-07 18:57
// Filename: solution.cpp
// Description:
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int dp[m+1][n+1];
        memset(dp, 0, sizeof(dp));
        int tm, tn;
        for(auto s: strs)
        {
            tm = tn = 0;
            for(auto c: s)
                if(c == '0')
                    tm++;
                else
                    tn++;
            for(int i = m; i >= tm; i--)
                for(int j = n; j >= tn; j--)
                    dp[i][j] = max(dp[i][j], dp[i-tm][j-tn] + 1);
        }
        return dp[m][n];
    }
};
