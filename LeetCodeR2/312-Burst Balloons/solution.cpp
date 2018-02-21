class Solution {
public:
    int dfs(map<pair<int, int>, int> &mem, vector<int> nums, int left, int right)
    {
        if(left + 1 >= right)
            return 0;
        if(mem.find({left, right}) != mem.end())
            return mem[{left, right}];
        int ans = 0;
        for(int i = left + 1; i < right; i++)
            ans = max(ans, nums[left] * nums[i] * nums[right] + dfs(mem, nums, left, i) + dfs(mem, nums, i, right));
        mem[{left, right}] = ans;
        return ans;
    }
    int maxCoins(vector<int>& nums) {
        int ans = 0;
        nums.insert(nums.begin(), 1);
        nums.insert(nums.end(), 1);
        map<pair<int, int>, int> mem;
        int n = nums.size();
        return dfs(mem, nums, 0, n - 1);
    }
};
