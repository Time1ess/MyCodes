// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-28 10:57
// Last modified: 2017-08-28 10:57
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
    int minDepth(TreeNode* root) {
        if(root == NULL)
            return 0;
        else if(root->left && root->right)
            return 1 + min(minDepth(root->left), minDepth(root->right));
        else if(root->left)
            return 1 + minDepth(root->left);
        else
            return 1 + minDepth(root->right);
        
    }
};
