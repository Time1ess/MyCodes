// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-21 16:15
// Last modified: 2017-03-21 16:15
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
    void add_greater(TreeNode *root, int &sum)
    {
        if(root->right)
            add_greater(root->right, sum);
        sum += root->val;
        root->val = sum;
        if(root->left)
            add_greater(root->left, sum);
    }
    TreeNode* convertBST(TreeNode* root) {
        if(root == NULL)
            return root;
        int sum = 0;
        add_greater(root, sum);
        return root;
    }
};
