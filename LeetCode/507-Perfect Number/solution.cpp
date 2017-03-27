// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-27 22:10
// Last modified: 2017-03-27 22:10
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool checkPerfectNumber(int num) {
        if(num <= 1)
            return false;
        int sum = 1;
        int k = 2;
        for(int i = 2; i < num / k; i++)
        {
            if(num % i == 0)
            {
                sum += i + num / i;
                k = i;
            }
        }
        return sum == num;
    }
};
