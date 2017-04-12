// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-12 10:43
// Last modified: 2017-04-12 10:43
// Filename: solution3.cpp
// Description:
class Num
{
public:
    int val, prime, idx;
    Num(int val, int prime, int idx)
    {
        this->val = val;
        this->prime = prime;
        this->idx = idx;
    }
};

bool operator>(const Num &a, const Num &b)
{
    return a.val > b.val;
}

bool operator<(const Num &a, const Num &b)
{
    return a.val < b.val;
}

class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        priority_queue<Num, vector<Num>, greater<Num>> pq;
        int ugly[n] = {0};
        for(int i = 0; i < primes.size(); i++)
            pq.push(Num(primes[i], primes[i], 1));
            
        ugly[0] = 1;
        for(int i = 1; i < n; i++)
        {
            ugly[i] = pq.top().val;
            while(pq.top().val == ugly[i])
            {
                Num next = pq.top();
                pq.pop();
                pq.push(Num(next.prime * ugly[next.idx], next.prime, next.idx+1));
            }
        }
        return ugly[n-1];
    }
};
