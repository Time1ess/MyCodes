// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-26 08:52
// Last modified: 2017-09-26 08:52
// Filename: solution.cpp
// Description:
class Solution {
public:
    set<float> possible_answers(vector<int> nums)
    {
        set<float> ans;
        if(nums.size() == 0)
            return ans;
        else if(nums.size() == 1)
        {
            ans.insert(nums[0]);
            return ans;
        }
        for(int i = 1; i < nums.size(); i++)
        {
            vector<int> first(nums.begin(), nums.begin() + i);
            vector<int> second(nums.begin() + i, nums.end());
            set<float> first_possible = possible_answers(first);
            set<float> second_possible = possible_answers(second);
            for(auto x: first_possible)
                for(auto y: second_possible)
                {
                    ans.insert(x + y);
                    ans.insert(x * y);
                    ans.insert(x - y);
                    ans.insert(y - x);
                    if(x != 0)
                        ans.insert(y / x);
                    if(y != 0)
                        ans.insert(x / y);
                }
        }
        return ans;
    }
    bool judgePoint24(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        while(next_permutation(nums.begin(), nums.end()))
        {
            set<float> ans = possible_answers(nums);
            for(auto x: ans)
                if(abs(x - 24) < 1e-5)
                    return true;
        }
        return false;
    }
};
