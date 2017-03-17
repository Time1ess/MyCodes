// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-17 13:54
// Last modified: 2017-03-17 13:54
// Filename: solution.cpp
// Description:
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
public:
    stack<TreeNode *> s;
    void find_left(TreeNode *root)
    {
        while(root)
        {
            s.push(root);
            root = root->left;
        }
    }
    BSTIterator(TreeNode *root) {
        find_left(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        if(s.empty())
            return false;
        return true;
    }

    /** @return the next smallest number */
    int next() {
        TreeNode *t = s.top();
        s.pop();
        if(t->right)
            find_left(t->right);
        return t->val;
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
