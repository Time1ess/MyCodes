class MyCalendar {
private:
    vector<pair<int, int>> events;
public:
    MyCalendar() {
        
    }
    
    bool overlap(int s1, int e1, int s2, int e2)
    {
        return s2 < e1 && s1 < e2;
    }
    
    bool book(int start, int end) {
        int n = events.size();
        if(n == 0)
        {
            events.push_back({start, end});
            return true;
        }
        int l = 0, r = n - 1;
        while(l <= r)
        {
            int m = l + (r - l) / 2;
            if(overlap(start, end, events[m].first, events[m].second))
                return false;
            else if(events[m].first < start)
                l = m + 1;
            else
                r = m - 1;
        }
        if(l != 0 && overlap(start, end, events[l-1].first, events[l-1].second))
            return false;
        if(l != n && overlap(start, end, events[l].first, events[l].second))
            return false;
        events.insert(events.begin() + l, {start, end});
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar obj = new MyCalendar();
 * bool param_1 = obj.book(start,end);
 */
