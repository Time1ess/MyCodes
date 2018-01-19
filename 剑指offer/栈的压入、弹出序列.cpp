class Solution {
public:
    void push(stack<int> &s, vector<int> &pushV, vector<int> &popV, int &i, int &j)
    {
        while(i < pushV.size() && pushV[i] != popV[j])
            s.push(pushV[i++]);
    }
    
    void pop(stack<int> &s, vector<int> &popV, int &j)
    {
        while(j < popV.size() && !s.empty() && s.top() == popV[j])
            s.pop(), j++;
    }
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        int size_push = pushV.size(), size_pop = popV.size();
        int i = 0, j = 0;
        stack<int> s;
        while(i < size_push && j < size_pop)
        {
            push(s, pushV, popV, i, j);
            while(i < size_push && j < size_pop && pushV[i] == popV[j])
                i++, j++;
            if(i == size_push)
                break;
            pop(s, popV, j);
        }
        while(j < size_pop && !s.empty())
        {
            if(popV[j] != s.top())
                return false;
            j++;
            s.pop();
        }
        return true;
    }
};
