/**
 * Definition of Interval:
 * classs Interval {
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

bool cmp(const pair<int, bool> &a, const pair<int, bool> &b)
{
    if(a.first == b.first)
        return a.second;
    else
        return a.first < b.first;
}

class Solution {
public:
    /**
     * @param intervals: an array of meeting time intervals
     * @return: the minimum number of conference rooms required
     */
    int minMeetingRooms(vector<Interval> &intervals) {
        // Write your code here
        int n = intervals.size();
        if(n <= 1)
            return 1;
        vector<pair<int, bool>> ts;  // timestamp  -- is_start
        for(auto x: intervals)
        {
            ts.push_back({x.start, true});
            ts.push_back({x.end, false});
        }
        sort(ts.begin(), ts.end(), cmp);
        int cnt = 0;
        int ans = 0;
        for(auto x: ts)
        {
            if(x.second == true)
                cnt++;
            else
                cnt--;
            ans = max(ans, cnt);
        }
        return ans;
    }
};
