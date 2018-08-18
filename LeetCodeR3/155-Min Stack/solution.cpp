class MinStack {
private:
    long long cur_min;
    stack<long long> nums;
public:
    /** initialize your data structure here. */
    MinStack() {
        cur_min = INT_MAX;
    }
    
    void push(int x) {
        nums.push(x - cur_min);
        cur_min = min(cur_min, (long long)x);
    }
    
    void pop() {
        long long offset = nums.top();
        nums.pop();
        if (offset < 0) {
            cur_min -= offset;
        }
    }
    
    int top() {
        long long t = nums.top();
        return (t < 0 ? 0 : t) + cur_min;
    }
    
    int getMin() {
        return cur_min;
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
