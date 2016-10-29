// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-29 09:30
// Last modified: 2016-10-29 09:30
// Filename: solution.cpp
// Description:
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        multiset<int> s;
        for(auto row: matrix)
            for(auto val: row)
                s.emplace(val);
        int result = -1;
        for(auto val: s)
        {
            if(k==1)
                result=val;
            k--;
        }
        return result;
    }
};
