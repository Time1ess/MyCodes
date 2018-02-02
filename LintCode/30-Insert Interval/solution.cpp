/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */


class Solution {
public:
    /*
     * @param intervals: Sorted interval list.
     * @param newInterval: new interval.
     * @return: A new interval list.
     */
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        vector<Interval> ans;
        int size = intervals.size();
        int i = 0;
        bool inserted = false;
        while(i < size)
        {
            Interval it = intervals[i++];
            if(inserted)
                ans.push_back(it);
            else if(it.start > newInterval.end) // smaller than current
            {
                ans.push_back(newInterval);
                ans.push_back(it);
                inserted = true;
            }
            else if(it.end < newInterval.start)  // bigger than current
                ans.push_back(it);
            else // overlapping
            {
                newInterval.start = min(newInterval.start, it.start);
                newInterval.end = max(newInterval.end, it.end);
            }
        }
        if(i == size && !inserted)
            ans.push_back(newInterval);
        return ans;
    }
};
