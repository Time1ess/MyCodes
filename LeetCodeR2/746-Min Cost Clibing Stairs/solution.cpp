class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        int dp_m1 = 0, dp_m2 = 0, dp;
        for(int i = 2; i <= n; i++)
        {
            dp = min(dp_m1 + cost[i-1], dp_m2 + cost[i-2]);
            dp_m2 = dp_m1;
            dp_m1 = dp;
        }
        return dp;
    }
};
