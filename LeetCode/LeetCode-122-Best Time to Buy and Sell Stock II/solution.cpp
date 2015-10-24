class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int profit=0;
        int size=prices.size();
        bool can_buy=true;
        for(int i=0;i<size-1;i++)
        {
            if(prices[i]<prices[i+1]&&can_buy)
            {
                profit-=prices[i];
                can_buy=false;
            }
            else if(prices[i]>prices[i+1]&&!can_buy)
            {
                profit+=prices[i];
                can_buy=true;
            }
        }
        if(!can_buy)
        profit+=prices[size-1];
        return profit;
    }
};
