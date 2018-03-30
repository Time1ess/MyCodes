class Solution {
public:
    /**
     * @param nums: an array of Integer
     * @param target: target = nums[index1] + nums[index2]
     * @return: [index1 + 1, index2 + 1] (index1 < index2)
     */
    vector<int> twoSum(vector<int> &nums, int target) {
        // write your code here
        int l = 0, r = nums.size() - 1;
        while(l < r)
        {
            int s = nums[l] + nums[r];
            if(s == target)
                return {l + 1, r + 1};
            else if(s > target)
                r--;
            else
                l++;
        }
        return {-1, -1};
    }
};
