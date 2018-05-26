class Solution {
public:
    /**
     * @param n: An integer
     * @return: An integer
     */
    int climbStairs(int n) {
        if(n <= 0)
            return 0;
        else if(n == 1)
            return 1;
        else if(n == 2)
            return 2;
        int below_1 = 2, below_2 = 1, current;
        for(int i = 3; i <= n; i++)
        {
            current = below_1 + below_2;
            below_2 = below_1;
            below_1 = current;
        }
        return current;
    }
};
