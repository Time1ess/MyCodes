// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-02 09:20
// Last modified: 2017-04-02 09:20
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool isPerfectSquare(int num) {
        if(num >= 2147483647)
            return false;
        int s = 1, e = 46340, m, pm;
        while(s <= e)
        {
            m = (s + e) >> 1;
            pm = m * m;
            if(pm == num)
                return true;
            else if(pm < num)
                s = m + 1;
            else
                e = m - 1;
        }
        return false;
    }
};
