// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-14 10:40
// Last modified: 2017-04-14 10:40
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
    int height(TreeNode* root)
    {
        if(root == NULL)
            return 0;
        return max(height(root->left), height(root->right)) + 1;
    }
    bool isBalanced(TreeNode* root) {
        if(root == NULL)
            return true;
        int left, right;
        left = height(root->left);
        right = height(root->right);
        return abs(left-right) <= 1 && isBalanced(root->left) && isBalanced(root->right);
    }
};
