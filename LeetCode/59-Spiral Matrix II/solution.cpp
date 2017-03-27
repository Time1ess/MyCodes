// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-27 16:15
// Last modified: 2017-03-27 16:15
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> ans;
        if(n == 0)
            return ans;
        ans.resize(n);
        int i, j, v, k, c;
        for(i = 0; i < n; i++)
            ans[i].resize(n);
        v = 1;
        k = n;
        i = j = c = 0;
        while(k > 0)
        {
            for(; c < k; c++, j++)
                ans[i][j] = v++;
            i++;j--;k--;
            c = 0;
            for(; c < k; c++, i++)
                ans[i][j] = v++;
            i--;j--;
            c = 0;
            for(; c < k; c++, j--)
                ans[i][j] = v++;
            i--;j++;k--;
            c = 0;
            for(; c < k; c++, i--)
                ans[i][j] = v++;
            i++;j++;
            c = 0;
        }
        return ans;
    }
};
