// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-26 10:10
// Last modified: 2017-04-26 10:10
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int trap(vector<int>& height) {
        int level = 0, water = 0, l = 0, r = height.size() - 1, lower;
        while(l <= r)
        {
            lower = height[height[l] < height[r] ? l++: r--];
            level = max(level, lower);
            water += level - lower;
        }
        return water;
    }
};
