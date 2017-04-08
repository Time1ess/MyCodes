// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-08 08:39
// Last modified: 2017-04-08 08:39
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;
        if(numRows <= 0)
            return ans;
        ans.push_back(vector<int>(1, 1));
        for(int i = 1; i < numRows; i++)
        {
            vector<int> t;
            t.push_back(1);
            for(int j = 1; j < i; j++)
                t.push_back(ans[i-1][j-1]+ans[i-1][j]);
            t.push_back(1);
            ans.push_back(t);
        }
        return ans;
    }
};
