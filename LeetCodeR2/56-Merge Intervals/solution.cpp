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
    return a.start < b.start || (a.start == b.start && a.end < b.end);
}
class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> ans;
        int n = intervals.size();
        if(n == 0)
            return ans;
        else if(n == 1)
        {
            ans.push_back(intervals[0]);
            return ans;
        }
        sort(intervals.begin(), intervals.end(), cmp);
        Interval current(intervals[0].start, intervals[0].end), tmp;
        for(int i = 1; i < n; i++)
        {
            tmp = intervals[i];
            if(tmp.end <= current.end)  // Full overlapping
                continue;
            else if(tmp.start <= current.end)  // Part overlapping
                current.end = max(tmp.end, current.end);
            else  // No overlapping
            {
                ans.push_back(current);
                current = tmp;
            }
        }
        ans.push_back(current);
        return ans;
    }
};
