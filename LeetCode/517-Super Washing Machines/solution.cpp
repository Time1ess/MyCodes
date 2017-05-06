// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-06 10:04
// Last modified: 2017-05-06 10:04
// Filename: solution.cpp
// Description:
class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        int size = machines.size();
        if(size == 0)
            return 0;
        int presum[size + 1] = {0}, avg;
        for(int i = 1; i <= size; i++)
            presum[i] = presum[i-1] + machines[i-1];
        if(presum[size] % size != 0)
            return -1;
        else
            avg = presum[size] / size;
        int ans = 0;
        for(int i = 0; i < size; i++)
        {
            int l = i * avg - presum[i];
            int r = (size - 1 - i) * avg - (presum[size] - presum[i+1]);
            if(l > 0 && r > 0)
                ans = max(ans, l+r);
            else
                ans = max(ans, max(abs(l), abs(r)));
        }
        return ans;
    }
};
