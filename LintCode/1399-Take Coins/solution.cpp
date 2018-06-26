class Solution {
public:
    /**
     * @param list: The coins
     * @param k: The k
     * @return: The answer
     */
    int takeCoins(vector<int> &list, int k) {
        // Write your code here
        int n = list.size();
        if(n <= k)
            return 0;
        int cur = 0;
        for(int i = 0; i < k; i++) {
            cur += list[i];
        }
        int ans = cur;
        for(int i = 0; i < k; i++) {
            cur += list[n-1-i] - list[k-1-i];
            ans = max(ans, cur);
        }
        return ans;
    }
};
