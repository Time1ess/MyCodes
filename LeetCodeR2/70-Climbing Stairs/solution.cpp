class Solution {
public:
    int climbStairs(int n) {
        if(n == 1)
            return 1;
        else if(n == 2)
            return 2;
        int ways_m1 = 2, ways_m2 = 1, ways;
        for(int i = 3; i <= n; i++)
        {
            ways = ways_m1 + ways_m2;
            ways_m2 = ways_m1;
            ways_m1 = ways;
        }
        return ways;
    }
};
