class Solution {
public:
    bool canJump(vector<int>& nums) {
        int max_length = 0;
        int n = nums.size();
        for(int i = 0; i < n; i++)
        {
            if(i > max_length)
                return false;
            max_length = max(max_length, i + nums[i]);
        }
        return true;
    }
};
