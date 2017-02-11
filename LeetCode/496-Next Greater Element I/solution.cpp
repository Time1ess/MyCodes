// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-11 14:24
// Last modified: 2017-02-11 14:24
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
        map<int, int> great_map;
        stack<int> de_stack;
        vector<int> ans;
        for(int i=0; i < nums.size(); i++)
        {
            while(!de_stack.empty()&&de_stack.top()<nums[i])
            {
                great_map[de_stack.top()] = nums[i];
                de_stack.pop();
            }
            de_stack.push(nums[i]);
        }
        while(!de_stack.empty())
        {
            great_map[de_stack.top()] = -1;
            de_stack.pop();
        }
        for(int i=0; i < findNums.size(); i++)
        {
            ans.push_back(great_map[findNums[i]]);
        }
        return ans;
    }
};
