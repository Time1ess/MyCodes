class MyQueue {
private:
    stack<int> q1, q2;
public:
    MyQueue() {
        // do intialization if necessary
    }

    /*
     * @param element: An integer
     * @return: nothing
     */
    void push(int element) {
        // write your code here
        q1.push(element);
    }

    /*
     * @return: An integer
     */
    int pop() {
        int x = top();
        q2.pop();
        return x;
        // write your code here
    }

    /*
     * @return: An integer
     */
    int top() {
        if (q2.empty()) {
            while (!q1.empty()) {
                q2.push(q1.top());
                q1.pop();
            }
        }
        return q2.top();
        // write your code here
    }
};
