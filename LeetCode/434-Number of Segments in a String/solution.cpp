// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-14 10:35
// Last modified: 2017-04-14 10:35
// Filename: solution.cpp
// Description:
class Solution {
public:
    int countSegments(string s) {
        int cnt = 0;
        bool continue_chars = false;
        for(auto c:s)
        {
            if(c != ' ')
            {
                if(!continue_chars)
                {
                    cnt++;
                    continue_chars = true;
                }
            }
            else
                continue_chars = false;
        }
        return cnt;
    }
};
