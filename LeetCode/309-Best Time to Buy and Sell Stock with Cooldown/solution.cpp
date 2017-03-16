// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-16 11:45
// Last modified: 2017-03-16 11:45
// Filename: solution.cpp
// Description:
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // buy[i]: before day i the max profit of any sequence ended with buy
        // sell[i]: before day i the max profit of any sequence ended with sell
        // rest[i]: before day i the max profit of any sequence ended with rest
        //
        // transition:
        // buy[i] = max(buy[i-1], rest[i-1] - price)
        // sell[i] = max(sell[i-1], buy[i-1] + price)
        // rest[i] = max(sell[i-1], buy[i-1], rest[i-1])
        //
        // buy[i] <= rest[i] <= sell[i]
        // so:
        // rest[i] = max(sell[i-1], rest[i-1])
        // rest[i] = sell[i-1]
        // 
        // then:
        // buy[i] = max(sell[i-2] - price, buy[i-1])
        // sell[i] = max(buy[i-1] + price, sell[i-1])
        int last_sell = 0, last_buy = 0, buy = -1e9, sell = 0;
        for(auto price: prices)
        {
            last_buy = buy;
            buy = max(last_sell - price, last_buy);
            last_sell = sell;
            sell = max(last_buy + price, last_sell);
        }
        return sell;
    }
};
