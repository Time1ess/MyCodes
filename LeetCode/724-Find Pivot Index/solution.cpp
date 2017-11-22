class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int total_sum = accumulate(nums.begin(), nums.end(), 0), left_sum = 0;
        for(int i = 0; i < nums.size(); i++)
        {
            if(left_sum == (total_sum - nums[i] - left_sum))
                return i;
            left_sum += nums[i];
        }
        return -1;
    }
};
