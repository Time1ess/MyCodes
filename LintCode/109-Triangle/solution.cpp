class Solution {
public:
    /**
     * @param triangle: a list of lists of integers
     * @return: An integer, minimum path sum
     */
    int minimumTotal(vector<vector<int>> &triangle) {
        // write your code here
        int m = triangle.size();
        if(m == 1)
            return triangle[0][0];
        vector<vector<int>> dp(2, vector<int>(m, 0));
        dp[0][0] = triangle[0][0];
        for(int i = 1; i < m; i++) {
            int n = triangle[i].size();
            for(int j = 0; j < n; j++)
                if(j == 0)
                    dp[i%2][j] = triangle[i][j] + dp[(i+1)%2][j];
                else if(j == n - 1)
                    dp[i%2][j] = triangle[i][j] + dp[(i+1)%2][j-1];
                else 
                    dp[i%2][j] = triangle[i][j] + min(dp[(i+1)%2][j-1], dp[(i+1)%2][j]);
        }
        int ans = INT_MAX;
        for(int j = 0; j < triangle[m-1].size(); j++)
            ans = min(ans, dp[(m+1)%2][j]);
        return ans;
    }
};
