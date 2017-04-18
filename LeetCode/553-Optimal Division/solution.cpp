// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-18 16:23
// Last modified: 2017-04-18 16:23
// Filename: solution.cpp
// Description:
class Solution {
public:
    string optimalDivision(vector<int>& nums) {
        int size = nums.size();
        if(size == 0)
            return "";
        else if(size == 1)
            return to_string(nums[0]);
        else if(size == 2)
            return to_string(nums[0]) + "/" + to_string(nums[1]);
        string ans = to_string(nums[0]);
        for(int i = 1; i < size; i++)
            ans += i == 1 ? "/(" + to_string(nums[i]) : "/" + to_string(nums[i]);
        return ans + ")";
    }
};
