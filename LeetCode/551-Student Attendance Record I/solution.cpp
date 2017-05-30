// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-18 16:30
// Last modified: 2017-04-18 16:30
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool checkRecord(string s) {
        bool absent = false;
        int late = 0;
        for(auto c:s)
        {
            if(c == 'L')
            {
                late++;
                if(late == 3)
                    return false;
                continue;
            }
            late = 0;
            if(c == 'A')
            {
                if(absent)
                    return false;
                else
                    absent = true;
            }
        }
        return true;
            
    }
};
