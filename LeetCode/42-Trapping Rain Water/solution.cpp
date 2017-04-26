// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-26 10:04
// Last modified: 2017-04-26 10:07
// Filename: solution.cpp
// Description:
class Solution {
public:
    int trap(vector<int>& height) {
        int size = height.size();
        if(size == 0)
            return 0;
        int ans = 0, nons = 0;
        int i = 0, j, k = size - 1;
        while(i < size)
        {
            j = i + 1;
            nons = 0;
            while(j < size && height[i] > height[j])
            {
                nons += height[j];
                j++;
            }
            if(j == size) // There is no other elevation higher than height[i]
                break;
            ans += min(height[i], height[j]) * (j - i - 1) - nons;
            i = j;
        }
        while(k > i)
        {
            j = k - 1;
            nons = 0;
            while(j > i && height[k] > height[j])
            {
                nons += height[j];
                j--;
            }
            ans += min(height[k], height[j]) * (k - j - 1) - nons;
            k = j;
        }
        return ans;
    }
};
