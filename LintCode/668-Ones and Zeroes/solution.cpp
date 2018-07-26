class Solution {
public:
    /**
     * @param strs: an array with strings include only 0 and 1
     * @param m: An integer
     * @param n: An integer
     * @return: find the maximum number of strings
     */
    vector<int> CntZeroesAndOnes(const string& s) {
        vector<int> cnt(2, 0);
        for(auto c: s) {
            cnt[c-'0']++;
        }
        return cnt;
    }
    int findMaxForm(vector<string> &strs, int m, int n) {
        // write your code here
        int len = strs.size();
        if(len == 0) {
            return 0;
        }
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        // dp[i][j]: With number of 0s <= i, number of 1s <= j,
        // How many strings we can build

        for(int x = 0; x < len; x++) {
            vector<int> cnts = CntZeroesAndOnes(strs[x]);
            for(int i = m; i >= cnts[0]; i--) {
                for(int j = n; j >= cnts[1]; j--) {
                    dp[i][j] = max(dp[i][j], dp[i-cnts[0]][j-cnts[1]]+1);
                }
            }
        }
        return dp[m][n];
    }
};
