// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-26 14:30
// Last modified: 2017-06-26 14:30
// Filename: solution2.cpp
// Description:
#define INF 1005
class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int store[5] = {INF, INF, -INF, -INF, -INF};
        for(auto x: nums)
        {
            if(x < store[0])
            {
                store[1] = store[0];
                store[0] = x;
            }
            else if(x < store[1])
                store[1] = x;
            if(x > store[4])
            {
                store[2] = store[3];
                store[3] = store[4];
                store[4] = x;
            }
            else if(x > store[3])
            {
                store[2] = store[3];
                store[3] = x;
            }
            else if(x > store[2])
                store[2] = x;
        }
        return max(store[4] * store[3] * store[2], store[0] * store[1] * store[4]);
    }
};
