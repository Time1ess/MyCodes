class Solution {
public:
    int climbStairs(int n) {
        if(n <= 0) {
            return 0;
        } else if(n == 1) {
            return 1;
        } else if(n == 2) {
            return 2;
        }
        int ans, ans_m1 = 2, ans_m2 = 1;
        for(int i = 3; i <= n; i++) {
            ans = ans_m1 + ans_m2;
            ans_m2 = ans_m1;
            ans_m1 = ans;
        }
        return ans;
    }
};
