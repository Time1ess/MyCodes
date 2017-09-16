// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-16 10:22
// Last modified: 2017-09-16 10:22
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int nthUglyNumber(int n) {
        int uglies[n+1] = {0};
        uglies[1] = 1;
        int index_2 = 1, index_3 = 1, index_5 = 1;
        int factor_2 = 2, factor_3 = 3, factor_5 = 5;
        int cur_min;
        for(int i = 2; i <= n; i++)
        {
            cur_min = min(min(factor_2, factor_3), factor_5);
            uglies[i] = cur_min;
            if(factor_2 == cur_min)
                factor_2 = 2 * uglies[++index_2];
            if(factor_3 == cur_min)
                factor_3 = 3 * uglies[++index_3];
            if(factor_5 == cur_min)
                factor_5 = 5 * uglies[++index_5];
        }
        return uglies[n];
    }
};
