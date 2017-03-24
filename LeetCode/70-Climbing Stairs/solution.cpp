// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-24 09:57
// Last modified: 2017-03-24 09:57
// Filename: solution.cpp
// Description:
class Solution {
public:
    int climbStairs(int n) {
        if(n < 1)
            return 0;
        else if(n <= 2)
            return n;
        int m1, m2, ans;
        m2 = 1;
        m1 = 2;
        for(int i = 3; i <= n; i++)
        {
            ans = m1 + m2;
            m2 = m1;
            m1 = ans;
        }
        return ans;
    }
};
