// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-05 10:38
// Last modified: 2017-09-05 10:38
// Filename: solution.cpp
// Description:
class Solution {
public:
    int flipLights(int n, int m) {
        if(m == 0 || n == 0)
            return 1;
        else if(n == 1)
            return 2;
        else if(n == 2)
            return m == 1 ? 3 : 4;
        else if(m == 1)
            return 4;
        else if(m == 2)
            return 7;
        else
            return 8;
    }
};
