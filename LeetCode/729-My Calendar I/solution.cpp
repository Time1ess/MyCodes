class MyCalendar {
public:
    vector<pair<int, int>> events;
    MyCalendar() {
        
    }
    
    int bsearch(int start, int end)
    {
        int l = 0, r = events.size();
        while(l < r)
        {
            int m = l + (r - l) / 2;
            if(events[m].first == start)
                return m;
            else if(events[m].first < start)
                l = m + 1;
            else
                r = m;
        }
        return l;
    }
    
    bool book(int start, int end) {
        int idx = bsearch(start, end);
        cout<<idx<<endl;
        if(events.empty() || (idx == events.size() && events[idx-1].second <= start))
        {
            events.push_back(make_pair(start, end));
            return true;
        }
        else if((idx > 0 && events[idx].first >= end && events[idx-1].second <= start) || (idx == 0 && events[idx].first >= end))
        {
            events.insert(events.begin() + idx, make_pair(start, end));
            return true;
        }
        else
            return false;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar obj = new MyCalendar();
 * bool param_1 = obj.book(start,end);
 */
