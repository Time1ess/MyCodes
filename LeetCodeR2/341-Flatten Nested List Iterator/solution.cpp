/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class NestedIterator {
private:
    stack<NestedInteger> s;
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        for(int i = nestedList.size() - 1; i >= 0; i--)
            s.push(nestedList[i]);
    }
    
    void extract_to_next_int()
    {
        while(!s.empty())
        {
            NestedInteger ni = s.top();
            if(ni.isInteger())
                break;
            s.pop();
            vector<NestedInteger> nl = ni.getList();
            for(int i = nl.size() - 1; i >= 0; i--)
                s.push(nl[i]);
        }
    }

    int next() {
        NestedInteger ni = s.top();
        s.pop();
        while(!ni.isInteger())
        {
            vector<NestedInteger> nl = ni.getList();
            for(int i = nl.size() - 1; i >= 0; i--)
                s.push(nl[i]);
            ni = s.top();
            s.pop();
        }
        return ni.getInteger();
    }

    bool hasNext() {
        extract_to_next_int();
        return !s.empty();
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
