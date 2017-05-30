// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-09 15:00
// Last modified: 2017-05-09 15:00
// Filename: solution.cpp
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
    bool same(TreeNode *s, TreeNode *t)
    {
        if(s == NULL && t == NULL)
            return true;
        else if(s == NULL || t == NULL)
            return false;
        else if(s->val == t->val)
            return same(s->left, t->left) && same(s->right, t->right);
        else
            return false;
    }
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if(s == NULL && t == NULL)
            return true;
        else if(s == NULL || t == NULL)
            return false;
        else
            return same(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t);
    }
};
