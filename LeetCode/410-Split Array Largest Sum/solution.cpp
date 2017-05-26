// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-26 09:12
// Last modified: 2017-05-26 09:12
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool doable(vector<int>& nums, int cut, int mmax)
    {
        long long acc = 0;
        for(auto x: nums)
        {
            if(x > mmax)
                return false;
            else if(x + acc <= mmax)
                acc += x;
            else
            {
                --cut;
                acc = x;
                
                if(cut < 0)
                    return false;
            }
        }
        return true;
    }
    
    int splitArray(vector<int>& nums, int m) {
        long long left = 0, right = 0;
        for(auto x: nums)
        {
            left = max(left, (long long)x);
            right += x;
        }
        while(left < right)
        {
            long long mid = left + (right - left) / 2;
            if(doable(nums, m-1, mid))
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }
};
