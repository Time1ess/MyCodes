class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        int write_idx = 0, read_idx = 0;
        while(read_idx < n) {
            if(nums[read_idx] != 0) {
                nums[write_idx++] = nums[read_idx];
            }
            read_idx++;
        }
        while(write_idx < n) {
            nums[write_idx++] = 0;
        }
    }
};
