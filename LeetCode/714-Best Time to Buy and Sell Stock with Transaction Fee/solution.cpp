class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        if(n <= 1)
            return 0;
        int tmp, unhold = 0, hold = -prices[0], max_profit = 0;
        for(int i = 1; i < n; i++)
        {
            tmp = unhold;
            unhold = max(unhold, hold + prices[i] - fee);
            hold = max(hold, tmp - prices[i]);
            max_profit = max(unhold, hold);
        }
        return max_profit;
    }
};
