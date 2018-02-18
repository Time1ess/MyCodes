class MyCalendarThree {
private:
    map<int, int> events;
public:
    MyCalendarThree() {
        
    }
    
    int book(int start, int end) {
        events[start]++;
        events[end]--;
        int on_going = 0, k = 0;
        for(auto x: events)
            k = max(k, on_going+=x.second);
        return k;
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree obj = new MyCalendarThree();
 * int param_1 = obj.book(start,end);
 */
