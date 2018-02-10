class Solution {
public:
    /*
     * @param prices: Given an integer array
     * @return: Maximum profit
     */
    int maxProfit(vector<int> &prices) {
        // write your code here
        int n = prices.size();
        if(n == 0)
            return 0;
        vector<int> minimum(n, INT_MAX);
        minimum[0] = prices[0];
        for(int i = 1; i < n; i++)
            minimum[i] = min(prices[i], minimum[i-1]);
        int ans = 0;
        for(int i = 0; i < n; i++)
            ans = max(ans, prices[i] - minimum[i]);
        return ans;
    }
};
