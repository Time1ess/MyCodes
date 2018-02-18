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
private:
    map<int, int> prefix, suffix;
    unordered_set<int> showups;
public:
    /** Initialize your data structure here. */
    SummaryRanges() {
        
    }
    
    void addNum(int val) {
        if(showups.find(val) != showups.end())
            return;
        showups.insert(val);
        auto it = prefix.find(val+1);
        auto it2 = suffix.find(val-1);
        if(it == prefix.end() && it2 == suffix.end())   // disjoint
        {
            prefix[val] = val;
            suffix[val] = val;
        }
        else if(it2 == suffix.end())
        {
            int end = it->second;
            prefix.erase(val+1);
            prefix[val] = end;
            suffix[end] = val;
        }
        else if(it == prefix.end())
        {
            int start = it2->second;
            suffix.erase(val-1);
            suffix[val] = start;
            prefix[start] = val;
        }
        else  // ..., start, val, end, ...
        {
            int end = it->second;
            int start = it2->second;
            prefix.erase(val+1);
            prefix[start] = end;
            suffix.erase(val-1);
            suffix[end] = start;
        }
    }
    
    vector<Interval> getIntervals() {
        vector<Interval> ans;
        for(auto x: prefix)
            ans.push_back({x.first, x.second});
        return ans;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges obj = new SummaryRanges();
 * obj.addNum(val);
 * vector<Interval> param_2 = obj.getIntervals();
 */
