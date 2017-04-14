// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-14 10:52
// Last modified: 2017-04-14 10:52
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
    void traverse(TreeNode *root, vector<string> &ans, string cur)
    {
        if(root == NULL)
            return;
        cur += to_string(root->val);
        if(root->left)
            traverse(root->left, ans, cur+"->");
        if(root->right)
            traverse(root->right, ans, cur+"->");
        if(!root->left && !root->right)
            ans.push_back(cur);
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> ans;
        if(root == NULL)
            return ans;
        string cur = "";
        traverse(root, ans, cur);
        return ans;
    }
};
