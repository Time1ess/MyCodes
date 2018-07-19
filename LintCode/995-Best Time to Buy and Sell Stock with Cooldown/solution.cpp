class Solution {
public:
    /**
     * @param prices: a list of integers
     * @return: return a integer
     */
    int maxProfit(vector<int> &prices) {
        // write your code here
        int n = prices.size();
        vector<int> buy(n+1, 0);
        vector<int> sell(n+1, 0);
        vector<int> rest(n+1, 0);
        buy[0] = INT_MIN;
        for(int i = 1; i <= n; i++) {
            int price = prices[i-1];
            buy[i] = max(buy[i-1], rest[i-1]-price);
            sell[i] = max(sell[i-1], buy[i-1]+price);
            rest[i] = max(rest[i-1], sell[i-1]);
        }
        return max(sell[n], rest[n]);
    }
};
