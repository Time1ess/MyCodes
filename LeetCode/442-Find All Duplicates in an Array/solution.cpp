// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-02 10:44
// Last modified: 2017-03-02 10:45
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> ans;
        int size = nums.size();
        int idx;
        for(int i=0; i < size; i++)
        {
            idx = abs(nums[i]) - 1;
            nums[idx] = -nums[idx];
            if(nums[idx] > 0)
                ans.push_back(idx + 1);
        }
        return ans;
    }
};
