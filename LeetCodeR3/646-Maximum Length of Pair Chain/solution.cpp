bool cmp(const vector<int>& a, const vector<int>& b) {
    return a[1] < b[1] || (a[1] == b[1] && a[0] < b[0]);
}
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        int n = pairs.size();
        if (n <= 1) {
            return n;
        }
        sort(pairs.begin(), pairs.end(), cmp);
        vector<int> dp(n, 0);
        int ans = 1;
        dp[0] = 1;
        for (int i = 1; i < n; i++) {
            dp[i] = 1;
            for (int j = i - 1; j >= 0; j--) {
                if (pairs[j][1] < pairs[i][0]) {
                    dp[i] = max(1 + dp[j], dp[i]);
                    ans = max(ans, dp[i]);
                }
            }
        }
        return ans;
    }
};
