// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-01-17 13:45
// Last modified: 2017-01-17 13:45
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> ans;
        for(int i=0; i < nums.size(); i++)
        {
            int idx = abs(nums[i])-1;
            if(nums[idx] > 0)
                nums[idx] = -nums[idx];
        }
        for(int i=0; i < nums.size(); i++)
        {
            if(nums[i] > 0)
                ans.push_back(i+1);
        }
        return ans;
    }
};
