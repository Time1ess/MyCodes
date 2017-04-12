// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-12 09:55
// Last modified: 2017-04-12 09:55
// Filename: solution.cpp
// Description:
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int ugly[n], size = primes.size();
        int last_idx[size] = {0};
        ugly[0] = 1;
        for(int i = 1; i < n; i++)
        {
            ugly[i] = INT_MAX;
            for(int j = 0; j < size; j++)
                ugly[i] = min(ugly[i], primes[j] * ugly[last_idx[j]]);
            for(int j = 0; j < size; j++)
                while(primes[j] * ugly[last_idx[j]] <= ugly[i])
                    last_idx[j]++;
        }
        return ugly[n-1];
    }
};
