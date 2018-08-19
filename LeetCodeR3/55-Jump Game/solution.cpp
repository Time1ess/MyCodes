class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) {
            return true;
        }
        int max_dist = 0;
        for (int i = 0; i < n && i <= max_dist; i++) {
            max_dist = max(max_dist, nums[i] + i);
        }
        return max_dist >= n - 1;
    }
};
