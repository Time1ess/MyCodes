// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-13 10:38
// Last modified: 2017-02-13 10:38
// Filename: solution.cpp
// Description:
class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        int result = 0;
        if(timeSeries.empty())
            return result;
        int last, now;
        int overlapped;
        for(int i=0; i < timeSeries.size(); i++)
        {
            if(i == 0)
            {
                last = timeSeries[i];
                result += duration;
            }
            else
            {
                now = timeSeries[i];
                overlapped = now - last - duration;
                if(overlapped < 0)
                    result += overlapped;
                result += duration;
                last = now;
            }
        }
        return result;
    }
};
