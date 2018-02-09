class Solution {
public:
    int minMoves(vector<int>& nums) {
        int n = nums.size();
        int min_num = INT_MAX;
        for(int i = 0; i < n; i++)
            min_num = min(min_num, nums[i]);
        int sum = accumulate(nums.begin(), nums.end(), 0);
        return sum - min_num * n;
    }
};
