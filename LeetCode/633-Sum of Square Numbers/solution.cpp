// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-22 08:58
// Last modified: 2017-09-22 08:58
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool judgeSquareSum(int c) {
        int l = 0, r = sqrt(c);
        while(l <= r)
        {
            int mid = l * l + r * r;
            if(mid == c)
                return true;
            else if(mid < c)
                l++;
            else
                r--;
        }
        return false;
    }
};
