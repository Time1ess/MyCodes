// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-14 17:26
// Last modified: 2017-10-14 17:26
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
    bool in_subtree(TreeNode* root, TreeNode *p)
    {
        if(root == NULL)
            return false;
        return root == p || in_subtree(root->left, p) || in_subtree(root->right, p);
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == NULL || root == p || root == q)
            return root;
        bool p_in_l = in_subtree(root->left, p);
        bool q_in_l = in_subtree(root->left, q);
        if(p_in_l && q_in_l)
            return lowestCommonAncestor(root->left, p, q);
        else if(!p_in_l && !q_in_l)
            return lowestCommonAncestor(root->right, p, q);
        else
            return root;
    }
};
