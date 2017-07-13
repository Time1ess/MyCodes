// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-13 10:00
// Last modified: 2017-07-13 10:00
// Filename: solution.cpp
// Description:
class Solution {
public:
    int minimum_price(vector<int> &price, vector<vector<int>> &special, vector<int>& needs,
                      int idx, int item_size)
    {
        if(idx == special.size())
        {
            int normal_price = 0;
            for(int k = 0; k < needs.size(); k++)
                normal_price += needs[k] * price[k];
            return normal_price;
        }
        int max_buy_count = 6;
        for(int k = 0; k < item_size; k++)
            max_buy_count = min(max_buy_count, special[idx][k] == 0 ? 6 : needs[k] / special[idx][k]);
        int best = 1e9;
        for(int buy_cnt = 0; buy_cnt <= max_buy_count; buy_cnt++)
        {
            for(int k = 0; k < item_size; k++)
                needs[k] -= special[idx][k] * buy_cnt;
            best = min(best, buy_cnt * special[idx][item_size] + minimum_price(price, special, needs,
                                                                               idx+1, item_size));
            for(int k = 0; k < item_size; k++)
                needs[k] += special[idx][k] * buy_cnt;
        }
        return best;
    }
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        int item_size = price.size();
        int best = minimum_price(price, special, needs, 0, item_size);
        return best;
    }
};
