// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-27 11:05
// Last modified: 2017-03-27 11:05
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
    void preorder(vector<vector<int>> &ans, TreeNode* root, int depth)
    {
        if(ans.size() == depth)
        {
            vector<int> level_ans;
            ans.push_back(level_ans);
        }
        ans[depth].push_back(root->val);
        if(root->left)
            preorder(ans, root->left, depth+1);
        if(root->right)
            preorder(ans, root->right, depth+1);
    }
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> ans;
        if(!root)
            return ans;
        preorder(ans, root, 0);
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
