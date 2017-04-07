// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-07 11:10
// Last modified: 2017-04-07 11:10
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
    bool symmetric(TreeNode *p, TreeNode *q)
    {
        if(p == NULL && q == NULL)
            return true;
        else if((p != NULL && q == NULL) || (q != NULL && p == NULL))
            return false;
        else
            return p->val == q->val && symmetric(p->left, q->right) && symmetric(p->right, q->left);
    }
    bool isSymmetric(TreeNode* root) {
        if(root == NULL)
            return true;
        return symmetric(root->left, root->right);
    }
};
