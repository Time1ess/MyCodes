// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-12 21:28
// Last modified: 2017-03-12 21:28
// Filename: solution.cpp
// Description:
class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        int size = timePoints.size();
        int ans = 1440, h, m, t;
        for(int i = 0; i < size; i++)
        {
            for(int j = i+1; j < size; j++)
            {
                h = m = 0;
                h = (timePoints[i][0] - timePoints[j][0]) * 10;
                h += timePoints[i][1] - timePoints[j][1];
                h *= 60;
                m = (timePoints[i][3] - timePoints[j][3]) * 10;
                m += timePoints[i][4] - timePoints[j][4];
                t = abs(h + m);
                t = min(t, 1440 - t);
                if(t < ans)
                    ans = t;
            }
        }
        return ans;
    }
};
