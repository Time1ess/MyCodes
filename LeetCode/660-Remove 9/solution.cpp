// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-15 08:51
// Last modified: 2017-08-15 08:51
// Filename: solution.cpp
// Description:
class Solution {
public:
    int newInteger(int n) {
        int ans = 0, base = 1;
        while(n > 0)
        {
            ans += n % 9 * base;
            n /= 9;
            base *= 10;
        }
        return ans;
    }
};
