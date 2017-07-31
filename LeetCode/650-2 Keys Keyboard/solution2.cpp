// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-31 09:27
// Last modified: 2017-07-31 09:27
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int minSteps(int n) {
        if(n <= 5)
            return n == 1 ? 0 : n;
        static const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        for(auto i: primes)
            if(n % i == 0)
                return i + minSteps(n / i);
        return n;
    }
};
