// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-06 10:49
// Last modified: 2017-09-06 10:49
// Filename: solution.cpp
// Description:
class MyStack {
private:
    queue<int> ql, qr;
    bool top_in_l, cont;
public:
    /** Initialize your data structure here. */
    MyStack() {
        top_in_l = false;
        cont = false;
    }
    
    /** Push element x onto stack. */
    void push(int x) {
        int tmp;
        queue<int> &src = top_in_l == true ? qr : ql;
        queue<int> &dst = top_in_l == true ? ql : qr;
        while(!src.empty())
        {
            tmp = src.front();
            src.pop();
            dst.push(tmp);
        }
        src.push(x);
        cont = false;
        top_in_l = !top_in_l;
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int tmp;
        queue<int> &src = top_in_l == true ? ql : qr;
        tmp = src.front();
        src.pop();
        if(!cont)
            top_in_l = !top_in_l;
        cont = true;
        return tmp;
    }
    
    /** Get the top element. */
    int top() {
        if(top_in_l)
            return ql.front();
        else
            return qr.front();
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return ql.empty() && qr.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack obj = new MyStack();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.top();
 * bool param_4 = obj.empty();
 */
