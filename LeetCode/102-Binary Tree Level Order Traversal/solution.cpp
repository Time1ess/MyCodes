// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-30 09:30
// Last modified: 2017-03-30 09:30
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
    void gen_level(TreeNode *root, vector<vector<int>> &ans, int depth)
    {
        if(ans.size() == depth)
        {
            vector<int> res;
            ans.push_back(res);
            ans.back().push_back(root->val);
        }
        else
            ans[depth].push_back(root->val);
        if(root->left)
            gen_level(root->left, ans, depth+1);
        if(root->right)
            gen_level(root->right, ans, depth+1);
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(root != NULL)
            gen_level(root, ans, 0);
        return ans;
    }
};
