class MyCalendarTwo {
private:
    map<int, int> bookings;
public:
    MyCalendarTwo() {
        
    }

    bool book(int start, int end) {
        bookings[start]++;
        bookings[end]--;
        int booked = 0;
        for(auto b: bookings) {
            booked += b.second;
            if(booked == 3) {
                bookings[start]--;
                bookings[end]++;
                return false;
            }
        }
        return true;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo obj = new MyCalendarTwo();
 * bool param_1 = obj.book(start,end);
 */
