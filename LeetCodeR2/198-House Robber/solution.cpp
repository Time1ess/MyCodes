class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 0)
            return 0;
        else if(n == 1)
            return nums[0];
        else if(n == 2)
            return max(nums[0], nums[1]);
        int day_m1 = max(nums[0], nums[1]), day_m2 = nums[0], today;
        for(int i = 2; i < n; i++)
        {
            today = max(day_m1, day_m2 + nums[i]);
            day_m2 = day_m1;
            day_m1 = today;
        }
        return today;
    }
};
