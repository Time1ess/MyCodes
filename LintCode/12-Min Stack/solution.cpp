class MinStack {
private:
    stack<long> s;
    long _min;
public:
    MinStack() {
        // do intialization if necessary
    }

    /*
     * @param number: An integer
     * @return: nothing
     */
    void push(int number) {
        // write your code here
        if(s.empty())
        {
            s.push(0);
            _min = number;
        }
        else
        {
            s.push(number - _min);
            if(number < _min)
                _min = number;
        }
    }

    /*
     * @return: An integer
     */
    int pop() {
        // write your code here
        int top = s.top();
        s.pop();
        int ans = top > 0 ? top + _min : _min;
        if(top < 0)
            _min -= top;
        return ans;
    }

    /*
     * @return: An integer
     */
    int min() {
        // write your code here
        return _min;
    }
};
