// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-16 10:11
// Last modified: 2017-09-16 10:11
// Filename: solution.cpp
// Description:
class Solution {
public:
    int nthUglyNumber(int n) {
        if(n <= 6)
            return n;
        priority_queue<long, vector<long>, greater<long>> pq;
        pq.push(2);
        pq.push(3);
        pq.push(5);
        n -= 2;
        while(n)
        {
            long x = pq.top();
            while(pq.top() == x)
                pq.pop();
            pq.push(x*2);
            pq.push(x*3);
            pq.push(x*5);
            n--;
        }
        return pq.top();
    }
};
