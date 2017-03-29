// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-29 10:36
// Last modified: 2017-03-29 10:36
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        if(s.length() <= 1)
            return false;
        int len = s.length();
        for(int part = 2; part <= len; part++)
        {
            if(len % part != 0)
                continue;
            int part_size = len / part;
            bool succeed = true;
            for(int pk = part_size; pk < len; pk += part_size)
            {
                for(int idx = 0; idx < part_size; idx++)
                {
                    if(s[idx] != s[pk + idx])
                    {
                        succeed = false;
                        break;
                    }
                }
                if(!succeed)
                    break;
            }
            if(succeed)
                return true;
        }
        return false;
    }
};
