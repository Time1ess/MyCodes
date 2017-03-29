// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-29 10:09
// Last modified: 2017-03-29 10:09
// Filename: solution2.cpp
// Description:
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int m1, m2;
        m1 = m2 = INT_MAX;
        for(auto x: nums)
        {
            if(x <= m1)
                m1 = x;
            else if(x <= m2)
                m2 = x;
            else
                return true;
        }
        return false;
    }
};
