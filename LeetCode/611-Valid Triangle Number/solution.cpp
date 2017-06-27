// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-27 11:19
// Last modified: 2017-06-27 11:19
// Filename: solution.cpp
// Description:
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int ans = 0;
        int size = nums.size();
        for(int i = 1; i < size; i++)
        {
            int l = 0, r = i - 1;
            while(l < r)
            {
                if(nums[l] + nums[r] > nums[i])
                    ans += r - l, r--;
                else
                    l++;
            }
        }
        return ans;
    }
};
