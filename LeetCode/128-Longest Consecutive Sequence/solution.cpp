// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-03 09:26
// Last modified: 2017-05-03 09:26
// Filename: solution.cpp
// Description:
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.size() == 0)
            return 0;
        unordered_set<int> s(nums.begin(), nums.end());
        int ans = 1;
        for(auto x: nums)
        {
            if(s.find(x) == s.end())
                continue;
            s.erase(x);
            int prev = x - 1, next = x + 1;
            while(s.find(prev) != s.end())
                s.erase(prev--);
            while(s.find(next) != s.end())
                s.erase(next++);
            ans = max(ans, next - prev - 1);
        }
        return ans;
    }
};
