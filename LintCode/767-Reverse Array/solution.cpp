class Solution {
public:
    /**
     * @param nums: a integer array
     * @return: nothing
     */
    void reverseArray(vector<int> &nums) {
        // write your code here
        int l = 0, r = nums.size() - 1;
        while(l < r)
            swap(nums[l++], nums[r--]);
    }
};
