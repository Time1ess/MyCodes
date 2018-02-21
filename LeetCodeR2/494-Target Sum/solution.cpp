class Solution {
public:
    void backtrack(int &ways, int current, const int target, vector<int> &nums, int idx, int n)
    {
        if(idx == n)
        {
            if(current == target)
                ways++;
            return;
        }
        backtrack(ways, current+nums[idx], target, nums, idx+1, n);
        backtrack(ways, current-nums[idx], target, nums, idx+1, n);
    }
    int findTargetSumWays(vector<int>& nums, int S) {
        int ways = 0;
        backtrack(ways, 0, S, nums, 0, nums.size());
        return ways;
    }
};
