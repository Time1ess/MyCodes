// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-01 14:48
// Last modified: 2017-09-01 14:48
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> maxes;
        vector<int> ans;
        for(int i = 0; i < nums.size(); i++)
        {
            if(!maxes.empty() && maxes.front() == i - k)
                maxes.pop_front();
            while(!maxes.empty() && nums[maxes.back()] <= nums[i])
                maxes.pop_back();
            maxes.push_back(i);
            if(i >= k-1)
                ans.push_back(nums[maxes.front()]);
        }
        return ans;
    }
};
