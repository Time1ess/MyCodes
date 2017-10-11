// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-11 09:48
// Last modified: 2017-10-11 09:48
// Filename: solution.cpp
// Description:
class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows == 1)
            return s;
        int length = s.length(), j = 0;
        string ans(length, ' ');
        int step = numRows * 2 - 2;
        for(int row = 0; row < numRows; row++)
        {
            for(int offset = 0, offset2 = step - 2 * row; row + offset < length || row + offset2 < length; offset += step, offset2 += step)
            {
                if(row + offset < length)
                    ans[j++] = s[row + offset];
                if(row != 0 && row != numRows - 1 && row + offset2 < length)
                    ans[j++] = s[row + offset2];
            }
        }
        return ans;
    }
};
