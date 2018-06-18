class MinStack {
private:
    long long minNum;
    stack<long long> s;
public:
    /** initialize your data structure here. */
    MinStack() {
    }
    
    void push(int x) {
        if(!s.empty()) {
            s.push((long long)x-minNum);
            minNum = x < minNum ? x : minNum;
        } else {
            s.push(0);
            minNum = x;
        }
    }
    
    void pop() {
        long long x = s.top();
        s.pop();
        if(x < 0)
            minNum -= x;
    }
    
    int top() {
        if(s.top() < 0)
            return minNum;
        return s.top() + minNum;
    }
    
    int getMin() {
        return minNum;
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
