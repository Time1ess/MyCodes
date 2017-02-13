// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-13 14:01
// Last modified: 2017-02-13 14:01
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> constructRectangle(int area) {
        vector<int> ans;
        for(int f1=sqrt(area);f1 > 0; f1--)
        {
            if(area % f1 == 0)
            {
                ans.push_back(area/f1);
                ans.push_back(f1);
                return ans;
            }
        }
    }
};
