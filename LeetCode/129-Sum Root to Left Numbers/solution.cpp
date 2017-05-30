// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-04 08:55
// Last modified: 2017-05-04 08:55
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
    void PreOrder(TreeNode* root, int &sum, int current)
    {
        if(root == NULL)
            return;
        current = 10 * current + root->val;
        if(!root->left && !root->right)
        {
            sum += current;
            return;
        }
        if(root->left)
            PreOrder(root->left, sum, current);
        if(root->right)
            PreOrder(root->right, sum, current);
    }
    int sumNumbers(TreeNode* root) {
        int sum = 0;
        PreOrder(root, sum, 0);
        return sum;
    }
};
