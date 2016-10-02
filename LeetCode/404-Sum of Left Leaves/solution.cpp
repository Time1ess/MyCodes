// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-02 10:15
// Last modified: 2016-10-02 10:15
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
    int sumOfLeftLeaves(TreeNode* root) {
        int val=0;
        if(root==NULL)
            return 0;
        TreeNode *left, *right;
        left = root->left;
        right = root->right;
        if(left!=NULL&&left->left==NULL&&left->right==NULL)
            val+=left->val;
        val += sumOfLeftLeaves(left);
        val += sumOfLeftLeaves(right);
        return val;
    }
};
