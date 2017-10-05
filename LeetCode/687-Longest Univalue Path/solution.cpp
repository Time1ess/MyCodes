// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-05 14:17
// Last modified: 2017-10-05 14:17
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
    int dfs(TreeNode* root, int &max_len)  // start from root(one direction), longest univalue path
    {
        if(root == NULL)
            return 0;
        int l = dfs(root->left, max_len);
        int r = dfs(root->right, max_len);
        int tl = root->left && root->left->val == root->val ? l + 1 : 0;
        int tr = root->right && root->right->val == root->val ? r + 1: 0;
        max_len = max(max_len, tl + tr);
        return max(tl, tr);
    }
    int longestUnivaluePath(TreeNode* root) {
        int max_len = 0;
        dfs(root, max_len);
        return max_len;
    }
};
