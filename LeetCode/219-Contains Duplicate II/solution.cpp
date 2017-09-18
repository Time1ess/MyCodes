// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-18 08:52
// Last modified: 2017-09-18 08:52
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> k_prev_neighbors;
        for(int i = 0; i < nums.size(); i++)
        {
            if(i > k)
                k_prev_neighbors.erase(nums[i-k-1]);
            if(k_prev_neighbors.find(nums[i]) != k_prev_neighbors.end())
                return true;
            k_prev_neighbors.insert(nums[i]);
        }
        return false;
    }
};
