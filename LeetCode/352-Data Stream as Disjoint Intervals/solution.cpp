// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-23 20:52
// Last modified: 2017-03-23 20:52
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
class SummaryRanges {
public:
    vector<Interval> intervals;
    /** Initialize your data structure here. */
    SummaryRanges() {
        
    }
    
    int binary_search(int start, int end, int val)
    {
        if(start == end)
            return -1;
        if(start + 1 == end && intervals[start].start < val)
            return start;
        
        int mid = (start + end) >> 1;
        if(intervals[mid].start == val)
            return mid;
        else if(intervals[mid].start > val)
            return binary_search(start, mid, val);
        else
            return binary_search(mid, end, val);
    }
    
    void addNum(int val) {
        int size = intervals.size();
        int idx = binary_search(0, size, val);
        
        if(idx != -1 && intervals[idx].end >= val)
            return;
        
        if(idx != size - 1 && val + 1 == intervals[idx+1].start)
            intervals[idx+1].start = val;
        else if(idx != -1 && val - 1 == intervals[idx].end)
            intervals[idx].end = val;
        else
            intervals.insert(intervals.begin() + idx + 1, Interval(val, val));
        
        if(idx != -1 && intervals[idx].end + 1 == intervals[idx+1].start)
        {
            intervals[idx].end = intervals[idx+1].end;
            intervals.erase(intervals.begin() + idx + 1);
        }
    }
    
    vector<Interval> getIntervals() {
        return intervals;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges obj = new SummaryRanges();
 * obj.addNum(val);
 * vector<Interval> param_2 = obj.getIntervals();
 */
