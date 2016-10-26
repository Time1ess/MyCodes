// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-26 10:39
// Last modified: 2016-10-26 10:39
// Filename: solution.cpp
// Description:
class Solution {
public:
    int cnt_bits(int n)
    {
        int c=0;
        while(n)
        {
            c++;
            n &=(n-1);
        }
        return c;
    }
    vector<string> readBinaryWatch(int num) {
        vector<string> ans;
        for(int h=0; h < 12; h++)
            for(int m=0; m < 60; m++)
                if(cnt_bits(h<<6 | m) == num)
                    ans.push_back(to_string(h)+(m < 10? ":0":":")+to_string(m));
        return ans;
    }
};
