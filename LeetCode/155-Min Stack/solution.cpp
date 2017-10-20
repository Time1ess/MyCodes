// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-20 15:07
// Last modified: 2017-10-20 15:07
// Filename: solution.cpp
// Description:
class MinStack {
private:
    stack<long> s;
    long min;
public:
    /** initialize your data structure here. */
    MinStack() {
    }
    
    void push(int x) {
        if(s.empty())
        {
            s.push(0);
            min = x;
        }
        else
        {
            s.push(x - min);
            if(min > x)
                min = x;
        }
    }
    
    void pop() {
        if(s.empty())
            return;
        long t = s.top();
        s.pop();
        if(t < 0)
            min = min - t;
    }
    
    int top() {
        long t = s.top();
        if(t > 0)
            return t + min;
        else
            return min;
    }
    
    int getMin() {
        return min;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
