class MyCalendarTwo {
private:
    multimap<pair<int, int>, int> intervals;
    multiset<pair<int, int>> overlaps;
public:
    MyCalendarTwo() {
        
    }
    
    bool isAlreadyBookingTwice(const pair<int, int>& p) {
        bool overlap = false;
        auto it = overlaps.insert(p);
        if(it != overlaps.begin()) {
            auto prevIt = prev(it);
            if(prevIt->second > p.first)
                overlap = true;
        }
        if(it != prev(overlaps.end())) {
            auto nextIt = next(it);
            if(p.second > nextIt->first)
                overlap = true;
        }
        overlaps.erase(it);
        return overlap;
    }
    
    bool book(int start, int end) {
        auto p = make_pair(start, end);
        if(isAlreadyBookingTwice(p))
            return false;
        auto it = intervals.insert(make_pair(p, end));
        if(it != intervals.begin()) {
            auto prevIt = prev(it);
            if(prevIt->second > start) {
                auto newOverlap = make_pair(start, min(prevIt->second, end));
                overlaps.insert(newOverlap);
            }
            it->second = max(prevIt->second, end);
        }
        auto nextIt = next(it);
        while(nextIt != intervals.end() && nextIt->first.first < end) {
            auto newOverlap = make_pair(nextIt->first.first,
                                        min(nextIt->first.second, end));
            overlaps.insert(newOverlap);
            nextIt->second = max(nextIt->second, end);
            nextIt = next(nextIt);
        }
        return true;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo obj = new MyCalendarTwo();
 * bool param_1 = obj.book(start,end);
 */
