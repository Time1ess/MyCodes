// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-03 17:11
// Last modified: 2017-03-03 17:14
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> split_possibles(vector<int> & nums, vector<char>& ops, int s, int e)
    {
        vector<int> ans;
        vector<int> part1, part2;
        if(s == e)
        {
            ans.push_back(nums[s]);
            return ans;
        }
        char op;
        for(int op_idx = s; op_idx < e; op_idx++)
        {
            op = ops[op_idx];
            part1 = split_possibles(nums, ops, s, op_idx);
            part2 = split_possibles(nums, ops, op_idx+1, e);
            if(!part1.empty() &&!part2.empty())
                for(auto x: part1)
                    for(auto y: part2)
                        if(op == '+')
                            ans.push_back(x+y);
                        else if(op == '-')
                            ans.push_back(x-y);
                        else if(op == '*')
                            ans.push_back(x*y);
            else if(!part1.empty())
                for(auto x: part1)
                    ans.push_back(x);
            else if(!part2.empty())
                for(auto x: part2)
                    ans.push_back(x);
        }
        return ans;
    }
    vector<int> diffWaysToCompute(string input) {
        vector<int> nums;
        vector<char> ops;
        vector<int> ans;

        int num = 0, nums_size, ops_size;
        for(auto c: input)
        {
            if(c >= '0' && c <= '9')
                num = num * 10 + c - '0';
            else
            {
                nums.push_back(num);
                num = 0;
                ops.push_back(c);
            }
        }
        nums.push_back(num);
        nums_size = nums.size();
        ops_size = ops.size();
        ans = split_possibles(nums, ops, 0, ops_size);
        return ans;
    }
};
