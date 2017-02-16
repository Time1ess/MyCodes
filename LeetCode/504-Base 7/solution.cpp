// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-16 08:55
// Last modified: 2017-02-16 08:55
// Filename: solution.cpp
// Description:
class Solution {
public:
    string convertToBase7(int num) {
        string sign;
        string digits="";
        int mod;
        if(num > 0)
            sign = "";
        else if(num < 0)
            sign = "-";
        else
            return "0";
        num = abs(num);
        while(num != 0)
        {
            mod = num % 7;
            num = num / 7;
            digits = to_string(mod)+digits;
        }
        return sign+digits;
    }
};
