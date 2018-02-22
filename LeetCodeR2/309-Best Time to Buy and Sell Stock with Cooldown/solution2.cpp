class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int last_buy = 0, last_sell = 0, buy = INT_MIN, sell = 0;
        for(auto price: prices)
        {
            last_buy = buy;
            buy = max(last_buy, last_sell - price);
            last_sell = sell;
            sell = max(last_sell, last_buy + price);
        }
        return sell;
    }
};
