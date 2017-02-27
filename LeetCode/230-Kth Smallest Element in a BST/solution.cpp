// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-27 21:34
// Last modified: 2017-02-27 21:35
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
    void inorder(TreeNode* root, int &ans, int &k)
    {
        if(root->left)
            inorder(root->left, ans, k);
        k--;
        if(k == 0)
        {
            ans = root->val;
            return;
        }
        if(root->right)
            inorder(root->right, ans, k);
    }
    int kthSmallest(TreeNode* root, int k) {
        int ans=0;
        inorder(root, ans, k);
        return ans;
    }
};
