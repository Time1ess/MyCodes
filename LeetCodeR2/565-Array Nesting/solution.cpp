class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        vector<bool> visited(n, false);
        for(int i = 0; i < n; i++)
        {
            int cur = 0;
            int x = i;
            while(!visited[x])
            {
                visited[x] = true;
                cur += 1;
                ans = max(ans, cur);
                x = nums[x];
            }
        }
        return ans;
    }
};
