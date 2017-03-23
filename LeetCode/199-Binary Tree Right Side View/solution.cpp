// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-23 10:22
// Last modified: 2017-03-23 10:22
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
    void dfs(vector<int> &ans, TreeNode* root, int depth)
    {
        int size = ans.size();
        if(depth < size)
            ans[depth] = root->val;
        else
            ans.push_back(root->val);
        if(root->left)
            dfs(ans, root->left, depth+1);
        if(root->right)
            dfs(ans, root->right, depth+1);
    }
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        if(root == NULL)
            return ans;
        dfs(ans, root, 0);
        return ans;
    }
};
