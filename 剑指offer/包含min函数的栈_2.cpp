class Solution {
public:
    void push(int value) {
        if(diffs.empty())
        {
            diffs.push(0);
            minimum = value;
        }
        else
        {
            diffs.push(value - minimum);
            if(value < minimum)
                minimum = value;
        }
    }
    void pop() {
        if(diffs.empty())
            throw new exception();
        int t = diffs.top();
        diffs.pop();
        if(t < 0)
            minimum -= t;
    }
    int top() {
        if(diffs.empty())
            throw new exception();
        int t = diffs.top();
        return t > 0? minimum + t : minimum;
    }
    int min() {
        if(diffs.empty())
            throw new exception();
        return minimum;
    }
private:
    stack<int> diffs;
    long minimum;
};
