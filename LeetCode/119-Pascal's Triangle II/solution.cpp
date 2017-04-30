// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-30 10:07
// Last modified: 2017-04-30 10:07
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> ans(rowIndex+1, 0);
        ans[0] = 1;
        for(int k = 1; k <= rowIndex; k++)
        {
            for(int i = k; i > 0; i--)
                ans[i] = ans[i-1] + ans[i];
        }
        return ans;
    }
};
