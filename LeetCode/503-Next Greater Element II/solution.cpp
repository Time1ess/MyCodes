// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-18 09:42
// Last modified: 2017-02-18 09:42
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int j;
        int size = nums.size();
        stack<int> s;
        vector<int> next(size, -1);
        for(int i = 0; i < 2 * size; i++)
        {
            j = i % size;
            while(!s.empty() && nums[j] > nums[s.top()])
            {
                next[s.top()] = nums[j];
                s.pop();
            }
            if(i < size)
                s.push(j);
        }
        return next;
    }
};
