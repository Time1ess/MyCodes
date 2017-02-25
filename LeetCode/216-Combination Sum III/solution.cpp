// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-25 10:10
// Last modified: 2017-02-25 10:10
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<vector<int>> find_combination(int k, int n, int mmax)
    {
        vector<vector<int>> ans;
        if(n <= 0)
            return ans;
        if(k == 1 && n <= mmax)
        {
            vector<int> x;
            x.push_back(n);
            ans.push_back(x);
            return ans;
        }
        vector<vector<int>> tans;
        for(int m=mmax; m >= 1; m--)
        {
            tans = find_combination(k-1, n-m, m-1);
            if(!tans.empty())
            {
                for(auto x: tans)
                {
                    x.push_back(m);
                    ans.push_back(x);
                }
            }
        }
        return ans;
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        return find_combination(k, n, 9);
    }
};
