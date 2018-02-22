class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> presum;
        int sum = 0;
        int ans = 0;
        presum[0] = 1;
        for(int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
            ans += presum[sum-k];
            presum[sum]+=1;
        }
        return ans;
    }
};
