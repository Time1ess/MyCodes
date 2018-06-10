class Solution {
public:
    /**
     * @param nums: a list of integers
     * @return: return a list of integers
     */
    vector<int> findDisappearedNumbers(vector<int> &nums) {
        // write your code here
        int n = nums.size();
        for (auto x: nums) {
            int v = abs(x) - 1;
            if (nums[v] > 0)
                nums[v] = -nums[v];
        }
        vector<int> ans;
        for (int i = 1; i <= n; i++)
            if (nums[i-1] > 0)
                ans.push_back(i);
        return ans;
    }
};
