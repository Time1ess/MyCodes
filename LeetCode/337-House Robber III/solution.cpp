// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-01 20:05
// Last modified: 2017-03-01 20:05
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
    int rob(TreeNode* root) {
        if(!root)
            return 0;
        int root_gain=0, child_gain=0;
        root_gain += root->val;
        if(root->left)
        {
            child_gain += rob(root->left);
            root_gain += rob(root->left->left);
            root_gain += rob(root->left->right);
        }
        if(root->right)
        {
            child_gain += rob(root->right);
            root_gain += rob(root->right->left);
            root_gain += rob(root->right->right);
        }
        return max(root_gain, child_gain);
    }
};
