// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-30 08:54
// Last modified: 2017-05-30 08:54
// Filename: solution.cpp
// Description:
class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        for(auto x: ops)
        {
            m = min(m, x[0]);
            n = min(n, x[1]);
        }
        return m * n;
    }
};
