class Solution {
public:
    /**
     * @param prices: Given an integer array
     * @return: Maximum profit
     */
    int maxProfit(vector<int> &prices) {
        // write your code here
        int last_hold = 0, last_no_hold = 0;
        int hold = 0, no_hold = 0;
        int n = prices.size();
        if(n <= 1)
            return 0;
        last_hold = -prices[0];
        for(int i = 1; i < n; i++)
        {
            hold = max(last_hold, last_no_hold - prices[i]);
            no_hold = max(last_no_hold, last_hold + prices[i]);
            last_hold = hold;
            last_no_hold = no_hold;
        }
        return no_hold;
    }
};
