// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-26 13:17
// Last modified: 2017-03-26 13:17
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
    int path_sum(TreeNode* root, int sums, int tar)
    {
        if(root == NULL)
            return 0;
        int s = root->val + sums;
        return (s == tar) + path_sum(root->left, s, tar) + path_sum(root->right, s, tar);
    }
    int pathSum(TreeNode* root, int sum) {
        if(root == NULL)
            return 0;
        return path_sum(root, 0, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
    }
};
