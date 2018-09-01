class Solution {
public:
    int rob(vector<int>& nums, int l, int r) {
        int include = 0, exclude = 0;
        for (int i = l; i <= r; i++) {
            int tmp = include;
            include = nums[i] + exclude;
            exclude = max(exclude, tmp);
        }
        return max(include, exclude);
    }
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) {
            return 0;
        } else if (n == 1) {
            return nums[0];
        } else if (n == 2) {
            return max(nums[0], nums[1]);
        }
        return max(rob(nums, 0, n - 2), rob(nums, 1, n - 1));
    }
};
