// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-17 09:37
// Last modified: 2017-03-17 09:37
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> ans;
        ans.push_back(0);
        int i, k;
        for(i = 0; i < n; i++)
        {
            for(k = ans.size() - 1; k >= 0; k--)
                ans.push_back(ans[k] | 1 << i);
        }
        return ans;
    }
};
