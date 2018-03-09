class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0; i < n; i++)
            if(nums[i] == 0)
                nums[i] = -1;
        int sum = 0;
        unordered_map<int, int> cnts;
        cnts[0] = -1;
        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            sum += nums[i];
            if(cnts.find(sum) != cnts.end())
                ans = max(ans, i - cnts[sum]);
            else
                cnts[sum] = i;
        }
        return ans;
    }
};
