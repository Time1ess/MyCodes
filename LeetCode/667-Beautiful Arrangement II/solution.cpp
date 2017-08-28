// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-28 10:45
// Last modified: 2017-08-28 10:45
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> constructArray(int n, int k) {
        vector<int> ans;
        int left = 2, right = n;
        bool left_side = false;
        ans.push_back(1);
        while(--k)
        {
            if(left_side)
                ans.push_back(left++);
            else
                ans.push_back(right--);
            left_side = !left_side;
        }
        if(left_side)
            for(int i = right; i >= left; i--)
                ans.push_back(i);
        else
            for(int i = left; i <= right; i++)
                ans.push_back(i);
        return ans;
    }
};
