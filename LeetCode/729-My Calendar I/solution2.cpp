class MyCalendar {
public:
    set<pair<int, int>> events;
    MyCalendar() {
        
    }
    
    
    bool book(int start, int end) {
        auto next = events.lower_bound(make_pair(start, end));
        if(next != events.end() && next->first < end) return false;
        if(next != events.begin() && (--next)->second > start) return false;
        events.insert(make_pair(start, end));
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar obj = new MyCalendar();
 * bool param_1 = obj.book(start,end);
 */
