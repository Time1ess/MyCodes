class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        int n = nums.size();
        for (int i = 0; i < n - 2; i++) {
            int l = i + 1, r = n - 1;
            while (l < r) {
                int s = nums[i] + nums[l] + nums[r];
                if (s == 0) {
                    vector<int> cur = {nums[i], nums[l], nums[r]};
                    ans.push_back(cur);
                    while (l < r && nums[r] == cur[2]) {
                        r--;
                    }
                    while (l < r && nums[l] == cur[1]) {
                        l++;
                    }
                } else if (s > 0) {
                    r--;
                } else {
                    l++;
                }
            }
            while (i < n - 2 && nums[i] == nums[i+1]) {
                i++;
            }
        }
        return ans;
    }
};
