/**
 * Definition of Interval:
 * classs Interval {
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 */

bool cmp(const Interval &a, const Interval &b)
{
    if(a.start < b.start)
        return true;
    else if(a.start == b.start && a.end < b.end)
        return true;
    else
        return false;
}


class Solution {
public:
    /*
     * @param intervals: interval list.
     * @return: A new interval list.
     */
    vector<Interval> merge(vector<Interval> &intervals) {
        vector<Interval> ans;
        int size = intervals.size();
        if(size == 0)
            return ans;
        sort(intervals.begin(), intervals.end(), cmp);
        int i = 0;
        while(i < size)
        {
            Interval tmp = intervals[i];
            int j = i + 1;
            while(j < size && intervals[j].start <= tmp.end)
            {
                tmp.end = max(tmp.end, intervals[j].end);
                j++;
            }
            ans.push_back(tmp);
            i = j;
        }
        return ans;
    }
};
