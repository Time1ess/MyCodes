// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-28 09:44
// Last modified: 2017-03-28 09:44
// Filename: solution.cpp
// Description:
class Solution {
public:
    void _combine(vector<vector<int>> &ans, vector<int> &res, int s, int n, int k)
    {
        if((n - s + 1) < k)
            return;
        if(k == 0)
        {
            ans.push_back(res);
            return;
        }
        for(int i = s; i <= n; i++)
        {
            res.push_back(i);
            _combine(ans, res, i+1, n, k-1);
            res.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> res;
        _combine(ans, res, 1, n, k);
        return ans;
    }
};
