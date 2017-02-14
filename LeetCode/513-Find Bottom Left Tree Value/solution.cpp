// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-14 08:44
// Last modified: 2017-02-14 08:44
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
    void LM_value(TreeNode* root, int depth, int &ans, int &ans_depth)
    {
        // assert root != NULL
        if(depth >= ans_depth)
        {
            ans = root->val;
            ans_depth = depth;
        }
        if(root->right != NULL)
            LM_value(root->right, depth+1, ans, ans_depth);
        if(root->left != NULL)
            LM_value(root->left, depth+1, ans, ans_depth);
    }
    int findBottomLeftValue(TreeNode* root) {
        int ans;
        int ans_depth=0;
        LM_value(root, 0, ans, ans_depth);
        return ans;
    }
};
