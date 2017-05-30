// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-25 13:58
// Last modified: 2017-04-25 13:58
// Filename: solution.cpp
// Description:
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        map<int, int> diffs;
        diffs[0] = -1;
        int cnts[2] = {0}, size = nums.size(), diff, ans = 0;
        for(int i = 0; i < size; i++)
        {
            cnts[nums[i]]++;
            diff = cnts[0] - cnts[1];
            auto x = diffs.find(diff);
            if(x != diffs.end())
                ans = max(ans, i - diffs[diff]);
            else
                diffs[diff] = i;
        }
        return ans;
    }
};
