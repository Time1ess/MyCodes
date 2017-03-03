// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-03 17:19
// Last modified: 2017-03-03 17:19
// Filename: solution2.cpp
// Description:
class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> ans;
        int size = input.size();
        for(int i=0; i < size; i++)
        {
            char ch = input[i];
            if(ch == '+' || ch == '-' || ch == '*')
            {
                vector<int> p1 = diffWaysToCompute(input.substr(0, i));
                vector<int> p2 = diffWaysToCompute(input.substr(i+1));
                for(auto x: p1)
                    for(auto y: p2)
                        if(ch == '+')
                            ans.push_back(x+y);
                        else if(ch == '-')
                            ans.push_back(x-y);
                        else
                            ans.push_back(x*y);
            }
        }
        if(ans.empty())
            ans.push_back(atoi(input.c_str()));
        return ans;
    }
};
