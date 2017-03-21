// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-21 16:26
// Last modified: 2017-03-21 16:26
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
    int depth(TreeNode *root, int &diameter)
    {
        int ld = 0, rd = 0;
        if(root->left)
            ld = 1 + depth(root->left, diameter);
        if(root->right)
            rd = 1 + depth(root->right, diameter);
        diameter = max(diameter, ld + rd);
        return max(ld, rd);
    }
    int diameterOfBinaryTree(TreeNode* root) {
        if(root == NULL)
            return 0;
        int diameter = 0;
        depth(root, diameter);
        return diameter;
    }
};
