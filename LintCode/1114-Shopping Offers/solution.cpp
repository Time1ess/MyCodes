class Solution {
public:
    /**
     * @param price: List[int]
     * @param special: List[List[int]]
     * @param needs: List[int]
     * @return: return an integer
     */
    void backtrack(vector<int>& price, vector<vector<int>>& special, vector<int> &needs, int& lowest_price, int current_price, int idx, int num_items, int num_special) {
        
        if(current_price >= lowest_price)
            return;
            
        if(idx == num_special) {
            for(int i = 0; i < num_items; i++)
                current_price += price[i] * needs[i];
            lowest_price = min(lowest_price, current_price);
            return;
        }
        
        int max_cnt = 6;
        for(int i = 0; i < num_items; i++)
            if(needs[i] != 0 && special[idx][i] != 0)
                max_cnt = min(max_cnt, needs[i] / special[idx][i]);

        for(int cnt = 0; cnt <= max_cnt; cnt++) {
            for(int i = 0; i < num_items; i++)
                needs[i] -= cnt * special[idx][i];
            backtrack(price, special, needs,
                      lowest_price, current_price + cnt * special[idx][num_items],
                      idx+1, num_items, num_special);
            for(int i = 0; i < num_items; i++)
                needs[i] += cnt * special[idx][i];
        }
    }
    int shoppingOffers(vector<int> &price, vector<vector<int>> &special, vector<int> &needs) {
        // write your code here
        int m = special.size();
        int n = price.size();
        int ans = INT_MAX;
        backtrack(price, special, needs, ans, 0, 0, n, m);
        return ans;
    }
};
