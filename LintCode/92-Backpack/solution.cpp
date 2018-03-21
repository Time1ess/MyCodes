class Solution {
public:
    /**
     * @param m: An integer m denotes the size of a backpack
     * @param A: Given n items with size A[i]
     * @return: The maximum size
     */
    int backPack(int m, vector<int> &A) {
        // write your code here
        int n = A.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(m+1, false));
        dp[0][0] = true;
        for(int i = 1; i <= n; i++)
            for(int k = 0; k <= m; k++)
            {
                dp[i][k] = dp[i-1][k];
                if(k >= A[i-1] && dp[i-1][k-A[i-1]])
                    dp[i][k] = true;
            }
        for(int k = m; k >= 1; k--)
            if(dp[n][k])
                return k;
        return 0;
    }
};
