class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> ans{-1, -1};
        int n = nums.size();
        int s = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
        int e = upper_bound(nums.begin(), nums.end(), target) - nums.begin();
        if(s == n || nums[s] != target)
            return ans;
        else
        {
            ans[0] = s;
            ans[1] = e - 1;
            return ans;
        }
    }
};
