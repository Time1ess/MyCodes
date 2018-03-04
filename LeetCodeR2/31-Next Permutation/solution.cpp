class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int idx = n - 2;
        while(idx >= 0 && nums[idx] >= nums[idx+1])
            idx--;
        if(idx == -1)
        {
            sort(nums.begin(), nums.end());
            return;
        }
        int swap_idx = idx + 1;
        for(int i = idx + 1; i < n; i++)
            if(nums[i] > nums[idx] && nums[swap_idx] > nums[i])
                swap_idx = i;
        swap(nums[idx], nums[swap_idx]);
        sort(nums.begin() + idx + 1, nums.end());
    }
};
