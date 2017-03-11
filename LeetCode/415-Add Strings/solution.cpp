// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-11 15:35
// Last modified: 2017-03-11 15:35
// Filename: solution.cpp
// Description:
class Solution {
public:
    string addStrings(string num1, string num2) {
        string s="";
        int i = num1.length() - 1;
        int j = num2.length() - 1;
        int k, adding=0;
        while(i >= 0 || j >= 0 || adding)
        {
            k = 0;
            if(i >= 0)
                k += (num1[i] - '0');
            if(j >= 0)
                k += (num2[j] - '0');
            k += adding;
            adding = k / 10;
            s += (k % 10 + '0');
            i--;
            j--;
        }
        reverse(s.begin(), s.end());
        return s;
    }
};
