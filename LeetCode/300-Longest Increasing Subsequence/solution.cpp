// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-03 10:47
// Last modified: 2017-04-03 10:47
// Filename: solution.cpp
// Description:
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> s;
        for(auto x: nums)
        {
            auto pos = lower_bound(s.begin(), s.end(), x);
            if(pos == s.end())
                s.push_back(x);
            else
                *pos = x;
        }
        return s.size();
    }
};
