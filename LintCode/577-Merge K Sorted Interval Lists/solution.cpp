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
 
struct PIntervalItem
{
    vector<Interval>::iterator cur, end;
    PIntervalItem(vector<Interval>::iterator cur, vector<Interval>::iterator end)
    {
        this->cur = cur;
        this->end = end;
    }
    bool operator<(const PIntervalItem &other) const
    {
        int s1 = cur->start;
        int s2 = (other.cur)->start;
        int e1 = cur->end;
        int e2 = (other.cur)->end;
        return s1 > s2 || (s1 == s2 && e1 > e2);
    }
};

class Solution {
public:
    /**
     * @param intervals: the given k sorted interval lists
     * @return:  the new sorted interval list
     */
    vector<Interval> mergeKSortedIntervalLists(vector<vector<Interval>> &intervals) {
        // write your code here
        vector<Interval> ans;
        priority_queue<PIntervalItem> pq;
        int n = intervals.size();
        for(int i = 0; i < n; i++)
        {
            if(intervals[i].begin() != intervals[i].end())
            {
                PIntervalItem pii(intervals[i].begin(), intervals[i].end());
                pq.push(pii);
            }
        }
        if(pq.empty())
            return {};
        Interval cur(INT_MIN, INT_MIN);
        bool first = true;
        while(!pq.empty())
        {
            PIntervalItem top = pq.top();
            int s = (top.cur)->start;
            int e = (top.cur)->end;
            pq.pop();
            if(cur.end < s)
            {
                if(!first)
                    ans.push_back(cur);
                cur.start = s;
                cur.end = e;
                first = false;
            }
            else
                cur.end = max(cur.end, e);
            ++(top.cur);
            if(top.cur != top.end)
                pq.push(top);
        }
        ans.push_back(cur);
        return ans;
    }
};
