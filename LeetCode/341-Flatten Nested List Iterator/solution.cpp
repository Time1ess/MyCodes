// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-17 14:27
// Last modified: 2017-03-17 14:27
// Filename: solution.cpp
// Description:
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
public:
    stack<NestedInteger> s;
    
    void flatten(vector<NestedInteger> &nestedList)
    {
        int size = nestedList.size();
        if(size == 0)
            return;
        for(int i = size - 1; i >= 1; i--)
            s.push(nestedList[i]);
        if(!nestedList[0].isInteger())
            flatten(nestedList[0].getList());
        else
            s.push(nestedList[0]);
    }
    NestedIterator(vector<NestedInteger> &nestedList) {
        flatten(nestedList);
    }

    int next() {
        NestedInteger x = s.top();
        s.pop();
        while(!x.isInteger())
        {
            flatten(x.getList());
            x = s.top();
            s.pop();
        }
        return x.getInteger();
    }

    bool hasNext() {
        if(s.empty())
            return false;
        NestedInteger x = s.top();
        while(!x.isInteger())
        {
            s.pop();
            flatten(x.getList());
            if(s.empty())
                return false;
            x = s.top();
        }
        return true;
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
