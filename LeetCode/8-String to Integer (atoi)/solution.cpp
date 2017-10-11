// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-11 10:36
// Last modified: 2017-10-11 10:36
// Filename: solution.cpp
// Description:
class Solution {
public:
    int myAtoi(string str) {
        int ans = 0;
        int sign = 1;
        int i = 0;
        while(str[i] == ' ')
            i++;
        if(str[i] == '-' || str[i] == '+')
            sign = 1 - 2 * (str[i++] == '-');
        while(str[i] >= '0' && str[i] <= '9')
        {
            if(ans > INT_MAX / 10 || (ans == INT_MAX / 10 && str[i] > '7'))
                if(sign == 1)
                    return INT_MAX;
                else
                    return INT_MIN;
            ans = ans * 10 + str[i++] - '0';
        }
        return sign * ans;
    }
};
