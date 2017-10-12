// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-12 20:32
// Last modified: 2017-10-12 20:32
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
bool cmp(const Interval &i1, const Interval &i2)
{
    return i1.start < i2.start;
}
class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        if(intervals.size() <= 1)
            return intervals;
        vector<Interval> ans;
        sort(intervals.begin(), intervals.end(), cmp);
        int s = intervals[0].start, e = intervals[0].end;
        ans.push_back(intervals[0]);
        for(int i = 1; i < intervals.size(); i++)
            if(intervals[i].start <= ans.back().end)
                ans.back().end = max(ans.back().end, intervals[i].end);
            else
                ans.push_back(intervals[i]);
        return ans;
    }
};
