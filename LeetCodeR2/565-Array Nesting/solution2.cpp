class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        for(int i = 0; i < n; i++)
        {
            int cur = 0;
            int x = i;
            while(nums[x] != INT_MAX)
            {
                int t = nums[x];
                nums[x] = INT_MAX;
                cur += 1;
                ans = max(ans, cur);
                x = t;
            }
        }
        return ans;
    }
};
