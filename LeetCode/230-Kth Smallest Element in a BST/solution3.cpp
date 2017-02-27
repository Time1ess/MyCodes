// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-27 21:30
// Last modified: 2017-02-27 21:35
// Filename: solution3.cpp
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
    int count(TreeNode* root)
    {
        if(root == NULL)
            return 0;
        return 1 + count(root->left) + count(root->right);
    }
    int kthSmallest(TreeNode* root, int k) {
        int cnt = count(root->left);
        if(k == cnt + 1)
            return root->val;
        else if(k <= cnt)
            return kthSmallest(root->left, k);
        else
            return kthSmallest(root->right, k-cnt-1);
    }
};
