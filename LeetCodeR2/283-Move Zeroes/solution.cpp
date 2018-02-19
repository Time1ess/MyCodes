class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        int zero_idx = 0, non_zero_idx = 0;
        do
        {
            while(zero_idx < n && nums[zero_idx] != 0)
                zero_idx++;
            non_zero_idx = zero_idx + 1;
            while(non_zero_idx < n && nums[non_zero_idx] == 0)
                non_zero_idx++;
            if(zero_idx == n || non_zero_idx == n)
                break;
            swap(nums[zero_idx], nums[non_zero_idx]);
        }while(true);
    }
};
