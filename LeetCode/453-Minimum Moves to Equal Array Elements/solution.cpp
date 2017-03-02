// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-02 20:14
// Last modified: 2017-03-02 20:14
// Filename: solution.cpp
// Description:
class Solution {
public:
    int minMoves(vector<int>& nums) {
        return accumulate(nums.begin(), nums.end(), 0) - nums.size() * *min_element(nums.begin(), nums.end());
    }
};
