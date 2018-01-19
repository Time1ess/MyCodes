class Solution {
public:
    void push(int value) {
        elements.push(value);
        min_s.push(!min_s.empty() && min_s.top() < value ? min_s.top() : value);
    }
    void pop() {
        if(elements.empty())
            throw new exception();
        elements.pop();
        min_s.pop();
    }
    int top() {
    	if(elements.empty())
            throw new exception();
        return elements.top();
    }
    int min() {
        if(min_s.empty())
            throw new exception();
        return min_s.top();
    }
private:
    stack<int> elements, min_s;
};
