class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if(nums.size() == 0)
            return 0;
        int ans = 1;
        int i = 0;
        for(int j = 1; j < nums.size(); j++)
        {
            if(nums[j] > nums[j-1])
                ans = max(ans, j - i + 1);
            else
                i = j;
        }
        return ans;
    }
};
