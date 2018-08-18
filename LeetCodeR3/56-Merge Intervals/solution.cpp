/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
bool cmp(const Interval& a, const Interval& b) {
    return a.start < b.start || (a.start == b.start && a.end < b.end);
}
class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        int n = intervals.size();
        if (n <= 1) {
            return intervals;
        }
        sort(intervals.begin(), intervals.end(), cmp);
        vector<Interval> ans;
        Interval cur = intervals[0];
        for (int i = 1; i < n; i++) {
            if (cur.end < intervals[i].start) {
                ans.push_back(cur);
                cur = intervals[i];
                continue;
            }
            cur.end = max(cur.end, intervals[i].end);
        }
        ans.push_back(cur);
        return ans;
    }
};
