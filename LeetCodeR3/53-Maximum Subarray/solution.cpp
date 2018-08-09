class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) {
            return 0;
        } else if(n == 1) {
            return nums[0];
        }
        int ans = nums[0];
        int cur = nums[0];
        for(int i = 1; i < n; i++) {
            if(cur < 0) {
                cur = nums[i];
            } else {
                cur += nums[i];
            }
            ans = max(ans, cur);
        }
        return ans;
    }
};
