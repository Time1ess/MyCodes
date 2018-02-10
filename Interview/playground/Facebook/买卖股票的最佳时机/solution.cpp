class Solution {
public:
    /*
     * @param prices: Given an integer array
     * @return: Maximum profit
     */
    int maxProfit(vector<int> &prices) {
        // write your code here
        int n = prices.size();
        if(n == 0)
            return 0;
        int minimum = INT_MAX;
        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            minimum = min(minimum, prices[i]);
            ans = max(ans, prices[i] - minimum);
        }
        return ans;
    }
};;
