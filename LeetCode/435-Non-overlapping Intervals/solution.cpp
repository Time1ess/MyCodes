// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-14 17:29
// Last modified: 2017-03-14 17:29
// Filename: solution.cpp
// Description:
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
bool cmp(const Interval &a, const Interval &b)
{
    return a.end < b.end;
}
class Solution {
public:

    int eraseOverlapIntervals(vector<Interval>& intervals) {
        int size = intervals.size();
        if(size == 0)
            return 0;
        sort(intervals.begin(), intervals.end(), cmp);
        
        int end = intervals[0].end;
        int non_overlapped = 1;
        for(int i = 1; i < size; i++)
        {
            if(intervals[i].start >= end)
            {
                non_overlapped++;
                end = intervals[i].end;
            }
        }
        return size - non_overlapped;
    }
};
