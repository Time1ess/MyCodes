class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 1);
        for(int i = 1; i < n; i++) {
            ans[i] = ans[i-1] * nums[i-1];
        }
        for(int i = n - 2, x = nums[n-1]; i >= 0; i--) {
            ans[i] *= x;
            x *= nums[i];
        }
        return ans;
    }
};
