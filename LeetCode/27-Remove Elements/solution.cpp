// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-02 09:39
// Last modified: 2017-04-02 09:39
// Filename: solution.cpp
// Description:
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int size = nums.size();
        int removed = 0;
        for(int i = 0; i < size; i++)
        {
            if(nums[i] == val)
                removed++;
            else
                nums[i - removed] = nums[i];
        }
        return size - removed;
    }
};
