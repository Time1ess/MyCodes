// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-12-08 19:35
// Last modified: 2016-12-08 19:35
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
 struct CmpItem {
     int value;
     int idx;
     CmpItem(int v, int i): value(v), idx(i) {}
 };
 
 bool cmp(const CmpItem &p, const CmpItem &q)
 {
     return p.value > q.value ? true:false;
 }
 
class Solution {
public:
    vector<int> findRightInterval(vector<Interval>& intervals) {
        int size = intervals.size();
        vector<int> ends, ans;
        vector<CmpItem> starts;
        for(int i=0; i < size; i++)
        {
            ends.push_back(intervals[i].end);
            starts.push_back(CmpItem(intervals[i].start, i));
        }
        sort(starts.begin(), starts.end(), cmp);
        for(int i=0; i < size; i++)
        {
            ans.push_back(binary_search(starts, 0, size, ends[i]));
        }
        return ans;
    }
    
    int binary_search(vector<CmpItem>& starts, int s, int e, int k)
    {
        if(s == e)
        {
            if(s > 0)
                return starts[s-1].idx;
            else
                return -1;
        }
        int m = (s+e)>>1;
        if(starts[m].value == k)
            return starts[m].idx;
        else if(starts[m].value > k)
            return binary_search(starts, m+1, e, k);
        else
            return binary_search(starts, s, m, k);
    }
};
