class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n < 2)
            return 0;
        else if(n == 2)
            return max(0, prices[1] - prices[0]);
        vector<int> buy(n, 0), sell(n, 0);
        buy[0] = -prices[0];
        buy[1] = max(-prices[0], -prices[1]);
        sell[1] = max(0, prices[1] - prices[0]);
        for(int i = 2; i < n; i++)
        {
            buy[i] = max(buy[i-1], sell[i-2] - prices[i]);
            sell[i] = max(sell[i-1], buy[i-1] + prices[i]);
        }
        return sell[n-1];
    }
};
