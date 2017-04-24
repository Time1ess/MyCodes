// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-24 16:29
// Last modified: 2017-04-24 16:29
// Filename: solution.cpp
// Description:
class Solution {
public:
    int maxArea(vector<int>& height) {
        int size = height.size();
        int i = 0, j = size-1;
        int maximum = 0, h;
        while(i < j)
        {
            h = min(height[i], height[j]);
            maximum = max(maximum, h * (j - i));
            while(h >= height[i] && i < j)
                i++;
            while(h >= height[j] && i < j)
                j--;
        }
        return maximum;
    }
};
