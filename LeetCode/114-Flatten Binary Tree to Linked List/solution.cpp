// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-27 13:44
// Last modified: 2017-06-27 13:44
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
    TreeNode* _flatten(TreeNode* root)
    {
        if(root == NULL)
            return NULL;
        TreeNode *head = root;
        TreeNode *left = _flatten(head->left);
        TreeNode *right = _flatten(head->right);
        head->left = NULL;
        head->right = NULL;
        if(left)
            head->right = left;
        while(head->right)
            head = head->right;
        head->right = right;
        return root;
    }
    void flatten(TreeNode* root) {
        root = _flatten(root);
    }
};
