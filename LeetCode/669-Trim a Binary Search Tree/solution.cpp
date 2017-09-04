// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-04 08:27
// Last modified: 2017-09-04 08:27
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
    TreeNode* trimBST(TreeNode* root, int L, int R) {
        if(root == NULL)
            return root;
        if(root->val < L)
            return trimBST(root->right, L, R);
        else if(root->val > R)
            return trimBST(root->left, L, R);
        else
        {
            root->left = trimBST(root->left, L, R);
            root->right = trimBST(root->right, L, R);
            return root;
        }
    }
};
