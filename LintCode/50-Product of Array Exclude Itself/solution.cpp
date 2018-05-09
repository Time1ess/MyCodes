class Solution {
public:
    /*
     * @param nums: Given an integers array A
     * @return: A long long array B and B[i]= A[0] * ... * A[i-1] * A[i+1] * ... * A[n-1]
     */
    vector<long long> productExcludeItself(vector<int> &nums) {
        // write your code here
        int n = nums.size();
        if(n == 0)
            return {};
        else if(n == 1)
            return {1};
        vector<long long> prefix_prods(n + 1, 1), suffix_prods(n + 1, 1);
        for(int i = 1; i <= n; i++)
            prefix_prods[i] = prefix_prods[i - 1] * nums[i - 1];
        for(int i = n - 2; i >= 0; i--)
            suffix_prods[i] = suffix_prods[i + 1] * nums[i + 1];
        vector<long long> ans;
        for(int i = 0; i < n; i++)
        {
            long long res = 1;
            if(i > 0)
                res *= prefix_prods[i];
            if(i < n - 1)
                res *= suffix_prods[i];
            ans.push_back(res);
        }
        return ans;
    }
};
