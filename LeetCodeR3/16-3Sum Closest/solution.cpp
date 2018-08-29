class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        if (n < 3) {
            return 0;
        }
        sort(nums.begin(), nums.end());
        int ans = INT_MAX;
        int ans_diff = INT_MAX;
        for (int i = 0; i < n - 2; i++) {
            int l = i + 1, r = n - 1;
            while (l < r) {
                int s = nums[i] + nums[l] + nums[r];
                int diff = s - target;
                if (abs(diff) < ans_diff) {
                    ans = s;
                    ans_diff = abs(diff);
                }
                if (diff == 0) {
                    return ans;
                } else if (diff > 0) {
                    r--;
                }  else {
                    l++;
                }
            }
        }
        return ans;
    }
};
