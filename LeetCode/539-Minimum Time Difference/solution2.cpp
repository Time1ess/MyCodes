// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-12 21:46
// Last modified: 2017-03-12 21:46
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        int size = timePoints.size();
        int ans = 1440, h, m, k, t;
        int buckets[1440] = {0};
        for(int i = 0; i < size; i++)
        {
            h = 10 * (timePoints[i][0] - '0') + timePoints[i][1] - '0';
            m = 10 * (timePoints[i][3] - '0') + timePoints[i][4] - '0';
            buckets[h * 60 + m]++;
        }
        for(int idx = 0; idx < 1440; idx++)
        {
            if(buckets[idx] == 0)
                continue;
            buckets[idx]--;
            for(int k = idx; k < 1440; k++)
            {
                if(buckets[k] == 0)
                    continue;
                t = abs(k-idx);
                t = min(t, 1440 - t);
                ans = min(t, ans);
            }
            buckets[idx]++;
        }
        return ans;
    }
};
