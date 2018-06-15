class Solution {
public:
    /**
     * @param nums: an array
     * @return: if it could become non-decreasing by modifying at most 1 element
     */
    bool checkPossibility(vector<int> &nums) {
        // Write your code here
        int n = nums.size();
        if(n <= 1)
            return true;
        bool canModify = true;
        if(nums[0] > nums[1])
        {
            nums[0] = nums[1];
            canModify = false;
        }
        int tmax = nums[1];
        for(int i = 1; i < n; i++) {
            tmax = max(tmax, nums[i]);
            if(tmax > nums[i]) {
                if(!canModify)
                    return false;
                canModify = false;
            }
        }
        return true;
    }
};
