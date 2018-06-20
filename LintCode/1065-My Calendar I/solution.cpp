bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    return a.first < b.first || (a.first == b.first && a.second < b.second);
}

class MyCalendar {
private:
    vector<pair<int, int>> bookings;
public:
    MyCalendar() {
        
    }
    
    bool book(int start, int end) {
        pair<int, int> p = make_pair(start, end);
        int n = bookings.size();
        if(n == 0) {
            bookings.push_back(p);
            return true;
        }
        int idx = lower_bound(bookings.begin(), bookings.end(), p, cmp) - bookings.begin();
        cout<<idx<<endl;
        if(idx > 0 && bookings[idx - 1].second > p.first) {
            // Not insert at first, check before
            return false;
        }
        if(idx < n && p.second > bookings[idx].first) {
            // Not insert at last, check after
            return false;
        }
        bookings.insert(bookings.begin() + idx, p);
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar obj = new MyCalendar();
 * bool param_1 = obj.book(start,end);
 */
