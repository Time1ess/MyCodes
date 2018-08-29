class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size();
        if (n == 0) {
            return 0;
        }
        int cur = 0;
        int j = 0;
        int ans = INT_MAX;
        for (int i = 0; i < n; i++) {
            cur += nums[i];
            while (j <= i && cur >= s) {
                ans = min(ans, i - j + 1);
                cur -= nums[j++];
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }
};
