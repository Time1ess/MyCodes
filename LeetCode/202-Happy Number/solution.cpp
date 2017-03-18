// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-18 09:17
// Last modified: 2017-03-18 09:17
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool isHappy(int n) {
        if(n <= 0)
            return false;
        int t, p, ps;
        map<int, bool> showups;
        while(n != 1)
        {
            if(showups[n] == true)
                return false;
            showups[n] = true;
            p = n;
            ps = 0;
            while(p)
            {
                t = p % 10;
                p /= 10;
                ps += pow(t, 2);
            }
            n = ps;
        }
        return true;
    }
};
