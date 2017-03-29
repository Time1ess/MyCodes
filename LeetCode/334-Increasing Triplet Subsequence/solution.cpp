// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-29 10:08
// Last modified: 2017-03-29 10:08
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int K = 3;
        int mmax[K];
        for(int i = 0; i < K; i++)
            mmax[i] = INT_MAX;
        for(auto x: nums)
        {
            for(int i = 0; i < K; i++)
            {
                if(i == K-1)
                    return true;
                if(x <= mmax[i])
                {
                    mmax[i] = x;
                    break;
                }
            }
        }
        return false;
    }
};
