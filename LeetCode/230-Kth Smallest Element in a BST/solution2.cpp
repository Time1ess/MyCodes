// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-27 21:20
// Last modified: 2017-02-27 21:35
// Filename: solution2.cpp
// Description:
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode *> s;
        TreeNode* p=root;
        while(true)
        {
            // search to the most left and lowest son
            // note the order of vals in s is big -> small(top)
            while(p)
            {
                s.push(p);
                p = p->left;
            }
            // fetch from stack, decrement 1 from k
            p = s.top();
            s.pop();
            k--;
            if(k == 0)
                return p->val;
            p = p->right;
        }
    }
};
