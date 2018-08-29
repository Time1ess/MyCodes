class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) {
            return 0;
        }
        int cur = 1;
        int ans = 0;
        int j = 0;
        for (int i = 0; i < n; i++) {
            cur *= nums[i];
            while (j <= i && cur >= k) {
                cur /= nums[j++];
            }
            ans += i - j + 1;
        }
        return ans;
    }
};
