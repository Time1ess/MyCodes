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
        vector<vector<bool>> dp(2, vector<bool>(m+1, false));
        dp[0][0] = true;
        for(int i = 1; i <= n; i++)
        {
            int src = (i+1) % 2, dst = i % 2;
            for(int k = 0; k <= m; k++)
            {
                dp[dst][k] = dp[src][k];
                if(k >= A[i-1] && dp[src][k-A[i-1]])
                    dp[dst][k] = true;
            }
        }
        int dst = n % 2;
        for(int k = m; k >= 1; k--)
            if(dp[dst][k])
                return k;
        return 0;
    }
};
