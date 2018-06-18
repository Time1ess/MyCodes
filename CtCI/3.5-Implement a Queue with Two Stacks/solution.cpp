class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        if(stack2.empty()) {
            while(!stack1.empty()) {
                int x = stack1.top();
                stack1.pop();
                stack2.push(x);
            }
        }
        int x = stack2.top();
        stack2.pop();
        return x;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};
