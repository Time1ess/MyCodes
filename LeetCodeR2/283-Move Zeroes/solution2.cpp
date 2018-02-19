class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        int idx = 0;
        for(auto x: nums)
            if(x != 0)
                nums[idx++] = x;
        while(idx < n)
            nums[idx++] = 0;
    }
};
