class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        vector<int> left_max(n, 0);
        vector<int> right_min(n, 0);
        left_max[0] = INT_MIN;
        for (int i = 1; i < n; i++) {
            left_max[i] = max(left_max[i-1], nums[i-1]);
        }
        right_min[n-1] = INT_MAX;
        for (int i = n - 2; i >= 0; i--) {
            right_min[i] = min(right_min[i+1], nums[i+1]);
        }
        int l = INT_MAX, r = INT_MIN;
        for (int i = 0; i < n; i++) {
            if (nums[i] > right_min[i]) {
                l = i;
                break;
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            if (nums[i] < left_max[i]) {
                r = i;
                break;
            }
        }
        if (l > r) {
            return 0;
        } else {
            return r - l + 1;
        }
    }
};
