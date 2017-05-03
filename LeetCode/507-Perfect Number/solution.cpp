// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-03 09:28
// Last modified: 2017-05-03 09:28
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool checkPerfectNumber(int num) {
        int sum = 1;
        for(int i = 2; i < sqrt(num); i++)
            if(num % i == 0)
                sum += i + (num / i == i ? 0 : num / i);
        return num != 1 and sum == num;
    }
};
