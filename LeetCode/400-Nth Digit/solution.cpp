// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-10 10:30
// Last modified: 2017-10-10 10:30
// Filename: solution.cpp
// Description:
class Solution {
public:
    int findNthDigit(int n) {
        int length = 1;
        long count = 9;
        int start = 1;
        while(n > length * count)
        {
            n -= length * count;
            length ++;
            count *= 10;
            start *= 10;
        }
        start += (n - 1) / length;
        return to_string(start)[(n - 1) % length] - '0';
    }
};
