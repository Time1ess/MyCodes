// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-25 09:11
// Last modified: 2017-05-25 09:11
// Filename: solution.cpp
// Description:
class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> m;
        for(auto x: nums)
            m[x]++;
        int mlen = 0;
        for(auto x: m)
            if(m.find(x.first+1) != m.end())
                mlen = max(mlen, x.second + m[x.first+1]);
        return mlen;
    }
};
