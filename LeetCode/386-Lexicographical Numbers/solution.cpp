// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-14 09:24
// Last modified: 2017-03-14 09:24
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> res(n);
        int k = 1;
        for(int i = 0; i < n; i++)
        {
            res[i] = k;
            if(10 * k <= n)
                k *= 10;
            else
            {
                if(k >= n)
                    k /= 10;
                k += 1;
                while(k % 10 == 0)
                    k /= 10;
            }
        }
        return res;
    }
};
