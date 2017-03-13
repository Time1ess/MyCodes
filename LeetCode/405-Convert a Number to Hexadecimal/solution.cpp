// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-13 08:52
// Last modified: 2017-03-13 08:52
// Filename: solution.cpp
// Description:
class Solution {
public:
    string toHex(int num) {
        if(num == 0)
            return "0";
        char *hex = "0123456789abcdef";
        int count = 0;
        string ans = "";
        while(num && count++ < 8)
        {
            ans += hex[num&0xf];
            num >>= 4;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
