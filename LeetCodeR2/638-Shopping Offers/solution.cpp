class Solution {
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        int ans = 0;
        int n = needs.size();
        // Buy with no offer
        for(int i = 0; i < n; i++)
            if(needs[i] != 0)
                ans += price[i] * needs[i];
        for(auto offer: special)
        {
            bool valid = true;
            vector<int> new_needs(needs.begin(), needs.end());
            for(int i = 0; i < n; i++)
                if(needs[i] < offer[i])
                {
                    valid = false;
                    break;
                }
                else
                    new_needs[i] -= offer[i];
            if(valid)
                ans = min(ans, offer[n] + shoppingOffers(price, special, new_needs));
        }
        return ans;
    }
};
