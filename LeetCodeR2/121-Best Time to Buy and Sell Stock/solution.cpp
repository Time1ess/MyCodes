class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int ans = 0;
        int min_price = INT_MAX;
        for(auto x: prices)
        {
            ans = max(ans, x - min_price);
            min_price = min(min_price, x);
        }
        return ans;
    }
};
