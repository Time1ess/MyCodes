class Solution {
public:
    bool canPartition(vector<int>& nums, vector<bool>& used, int idx, int n, int cur, int tar, int k) {
        if (k == 0) {
            return true;
        }
        if (cur == tar) {
            return canPartition(nums, used, 0, n, 0, tar, k - 1);
        }
        for (int i = idx; i < n; i++) {
            if (used[i] == false) {
                used[i] = true;
                if (canPartition(nums, used, i + 1, n, cur + nums[i], tar, k) == true) {
                    return true;
                }
                used[i] = false;
            }
        }
        return false;
    }
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int n = nums.size();
        vector<bool> used(n, false);
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0) {
            return false;
        }
        return canPartition(nums, used, 0, n, 0, sum / k, k);
    }
};
