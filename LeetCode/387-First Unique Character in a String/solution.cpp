// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-25 10:37
// Last modified: 2016-10-25 10:37
// Filename: solution.cpp
// Description:
class Solution {
public:
    int firstUniqChar(string s) {
        int m[1<<8];
        memset(m, 0, sizeof(m));
        for(auto c:s)
            m[c]++;
        for(auto c:s)
            if(m[c]==1)
                return s.find(c);
        return -1;
    }
};
