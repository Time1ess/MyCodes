// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-02 13:47
// Last modified: 2017-05-02 13:47
// Filename: solution.cpp
// Description:
class MyQueue {
private:
    stack<int> s1, s2;
public:
    /** Initialize your data structure here. */
    MyQueue() {
        
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        int t;
        while(!s2.empty())
        {
            t = s2.top();
            s2.pop();
            s1.push(t);
        }
        s1.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int t;
        while(!s1.empty())
        {
            t = s1.top();
            s1.pop();
            s2.push(t);
        }
        t = s2.top();
        s2.pop();
        return t;
    }
    
    /** Get the front element. */
    int peek() {
        int t;
        while(!s1.empty())
        {
            t = s1.top();
            s1.pop();
            s2.push(t);
        }
        t = s2.top();
        return t;
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return s1.empty() && s2.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue obj = new MyQueue();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.peek();
 * bool param_4 = obj.empty();
 */
