// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-03 13:28
// Last modified: 2017-03-03 13:28
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        vector<int> _ans;
        int l, r, t, s, i;
        int size = nums.size();
        for(i = 0; i < size - 1; i++)
        {
            
            t = -nums[i];
            l = i + 1;
            r = size - 1;
            while(l < r)
            {
                s = nums[l] + nums[r];
                if(t < s)
                    r--;
                else if(t > s)
                    l++;
                else
                {
                    _ans.push_back(nums[i]);
                    _ans.push_back(nums[l]);
                    _ans.push_back(nums[r]);
                    ans.push_back(_ans);
                    _ans.clear();
                    
                    l++;
                    r--;
                    while(l < r && nums[l] == _ans[1]) l++;
                    while(l < r && nums[r] == _ans[2]) r--;
                }
            }
            while(i < size - 1 && nums[i] == nums[i+1]) i++;
        }
        return ans;
    }
};
