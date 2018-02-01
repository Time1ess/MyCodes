/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer,
 *     // rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds,
 *     // if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds,
 *     // if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class NestedIterator {
private:
    stack<NestedInteger> s;
    
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        // Initialize your data structure here.
        int size = nestedList.size();
        for(int i = size - 1; i >= 0; i--)
            s.push(nestedList[i]);
    }

    // @return {int} the next element in the iteration
    int next() {
        // Write your code here
        NestedInteger ni = s.top();
        s.pop();
        while(!ni.isInteger())
        {
            vector<NestedInteger> l = ni.getList();
            int size = l.size();
            for(int i = size - 1; i >= 0; i--)
                s.push(l[i]);
            ni = s.top();
            s.pop();
        }
        return ni.getInteger();
    }

    // @return {boolean} true if the iteration has more element or false
    bool hasNext() {
        // Write your code here
        if(s.empty())
            return false;
        NestedInteger ni = s.top();
        if(ni.isInteger())
            return true;
        while(!ni.isInteger())
        {
            s.pop();
            vector<NestedInteger> l = ni.getList();
            int size = l.size();
            for(int i = size - 1; i >= 0; i--)
                s.push(l[i]);
            if(s.empty())
                return false;
            ni = s.top();
        }
        return true;
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) v.push_back(i.next());
 */
