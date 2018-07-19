class Solution {
public:
    /**
     * @param n: the number of integers
     * @param k: the number of distinct integers
     * @return: any of answers meet the requirment
     */
    vector<int> constructArray(int n, int k) {
        // Write your code here
        int l = 1, r = n;
        vector<int> ans;
        bool asc = true;
        while(--k) {
            ans.push_back(asc ? l++: r--);
            asc = !asc;
        }
        while(l <= r) {
            ans.push_back(asc ? l++: r--);
        }
        return ans;
    }
};
