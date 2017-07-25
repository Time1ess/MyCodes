// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-25 10:31
// Last modified: 2017-07-25 10:31
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        unordered_map<int, int> m;
        int size = nums.size();
        for(int i = 1; i <= size; i++)
            m[nums[i-1]]++;
        vector<int> ans(2, 0);
        for(int i = 1; i <= size; i++)
            if(m[i] == 2)
                ans[0] = i;
            else if(m[i] == 0)
                ans[1] = i;
        return ans;
    }
};
