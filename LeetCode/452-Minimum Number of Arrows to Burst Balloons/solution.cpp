// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-12-09 17:53
// Last modified: 2016-12-09 17:53
// Filename: solution.cpp
// Description:
class Solution {
public:
    int findMinArrowShots(vector<pair<int, int>>& points) {
        int cnt = 0;
        int size = points.size();
        if(size == 0)
            return cnt;
        sort(points.begin(), points.end());
        int end = points[0].second;
        cnt++;
        for(int i=1; i < size; i++)
        {
            if(points[i].first <= end && points[i].second < end)
                end = points[i].second;
            else if(points[i].first > end)
            {
                end = points[i].second;
                cnt++;
            }
        }
        return cnt;
    }
};
