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
    bool overlap(const Interval &a, const Interval &b)
    {
        return a.end > b.start && b.end > a.start;
    }
    
    int eraseOverlapIntervals(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);
        Interval current(INT_MIN, INT_MIN);
        int cnt = 0;
        for(auto x: intervals)
        {
            if(!overlap(current, x))
            {
                cnt++;
                current.end = max(current.end, x.end);
            }
        }
        return intervals.size() - cnt;
    }
};
