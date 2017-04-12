// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-12 10:09
// Last modified: 2017-04-12 10:09
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int size = primes.size();
        int vals[size], idx[size] = {0};
        int ugly[n];
        for(int i = 0; i < size; i++)
            vals[i] = 1;
        int next = 1;
        for(int i = 0; i < n; i++)
        {
            ugly[i] = next;
            
            next = INT_MAX;
            for(int j = 0; j < size; j++)
            {
                if(vals[j] == ugly[i])
                    vals[j] = primes[j] * ugly[idx[j]++];
                next = min(next, vals[j]);
            }
        }
        return ugly[n-1];
    }
};
