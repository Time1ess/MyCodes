// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-26 09:02
// Last modified: 2017-09-26 09:02
// Filename: solution2.cpp
// Description:
class Solution {
public:
    bool valid(float a, float b)
    {
        if(abs(a + b - 24) < 1e-5 || abs(a - b - 24) < 1e-5 || abs(a * b - 24) < 1e-5 || (b && abs(a / b - 24) < 1e-5))
            return true;
        return false;
    }
    bool valid(float a, float b, float c)
    {
        if(valid(a + b, c) || valid(a - b, c) || valid(a * b, c) || (b && valid(a / b, c)))return true;
        if(valid(a, b + c) || valid(a, b - c) || valid(a, b * c) || (c && valid(a, b / c)))return true;
        return false;
    }
    bool valid(float a, float b, float c, float d)
    {
        if(valid(a + b, c, d) || valid(a - b, c, d) || valid(a * b, c, d) || (b && valid(a / b, c, d)))return true;
        if(valid(a, b + c, d) || valid(a, b - c, d) || valid(a, b * c, d) || (c && valid(a, b / c, d)))return true;
        if(valid(a, b, c + d) || valid(a, b, c - d) || valid(a, b, c * d) || (d && valid(a, b, c / d)))return true;
        return false;
    }
    bool judgePoint24(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        do{
            if(valid(nums[0], nums[1], nums[2], nums[3]))
                return true;
        } while(next_permutation(nums.begin(), nums.end()));
        return false;
    }
};
