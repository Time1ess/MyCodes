class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        int write = 0, read = 0;
        while (read < n) {
            int j = read;
            while (j < n && nums[read] == nums[j]) {
                j++;
            }
            for (int k = read; k < min(j, read + 2); k++) {
                nums[write++] = nums[k];
            }
            read = j;
        }
        return write;
    }
};
