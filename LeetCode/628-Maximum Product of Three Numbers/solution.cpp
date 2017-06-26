// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-26 14:26
// Last modified: 2017-06-26 14:26
// Filename: solution.cpp
// Description:
#define INF 1005
class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int store[6] = {INF, INF, INF, -INF, -INF, -INF};
        for(auto x: nums)
        {
            if(x < 0)
            {
                if(x < store[0])
                {
                    store[2] = store[1];
                    store[1] = store[0];
                    store[0] = x;
                }
                else if(x < store[1])
                {
                    store[2] = store[1];
                    store[1] = x;
                }
                else if(x < store[2])
                    store[2] = x;
            }
            else 
            {
                if(x > store[5])
                {
                    store[3] = store[4];
                    store[4] = store[5];
                    store[5] = x;
                }
                else if(x > store[4])
                {
                    store[3] = store[4];
                    store[4] = x;
                }
                else if(x > store[3])
                    store[3] = x;
            }
        }
        int pos_cnt = 0, neg_cnt = 0;
        for(int i = 0; i < 6; i++)
            if(i < 3 && store[i] != INF)
                neg_cnt++;
            else if(i >= 3 && store[i] != -INF)
                pos_cnt++;
        if(pos_cnt == 3 && neg_cnt >= 2)
            return max(store[5] * store[4] * store[3], store[0] * store[1] * store[5]);
        else if(pos_cnt == 3)
            return store[5] * store[4] * store[3];
        else if(pos_cnt == 2 && neg_cnt >= 2)
            return store[5] * store[0] * store[1];
        else if(pos_cnt == 2)
                return store[5] * store[4] * store[0];
        else if(pos_cnt == 1)
            return store[5] * store[0] * store[1];
        else if(pos_cnt == 0)
            return store[0] * store[1] * store[2];
    }
};
