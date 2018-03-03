class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> ans{-1, -1};
        if(n == 0)
            return ans;
        int l = 0, r = n;
        while(l < r)
        {
            int m = l + (r - l) / 2;
            if(nums[m] >= target)
                r = m;
            else if(nums[m] < target)
                l = m + 1;
        }
        if(l == n || nums[l] != target)
            return ans;
        ans[0] = l;
        l = 0, r = n;
        while(l < r)
        {
            int m = l + (r - l) / 2;
            if(nums[m] <= target)
                l = m + 1;
            else
                r = m;
        }
        ans[1] = l - 1;
        return ans;
    }
};
