// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-02 09:33
// Last modified: 2017-03-02 09:33
// Filename: solution.cpp
// Description:
class Solution {
public:
    int countDigitOne(int n) {
        int l, r = n, x = 1;
        int ans = 0;
        while(r > 0)
        {
            l = r % 10;
            r = r / 10;
            ans += r * x;
            if(l == 1)
                ans += 1 + n % x;
            else if(l > 1)
                ans += x;
            x = x * 10;
        }
        return ans;
    }
};
