// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-17 09:56
// Last modified: 2017-03-17 09:56
// Filename: solution.cpp
// Description:
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buy_price = 1e9;
        int profit = 0;
        for(auto price: prices)
        {
            buy_price = min(buy_price, price);
            profit = max(profit, price - buy_price);
        }
        return profit;
    }
};
