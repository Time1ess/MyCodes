// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-18 08:46
// Last modified: 2017-08-18 08:46
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
    void match_sum(vector<vector<int>> &ans, vector<int> &current, TreeNode* root, int sum)
    {
        if(root == NULL)
            return;
        current.push_back(root->val);
        if(root->left == NULL && root->right == NULL && root->val == sum)
            ans.push_back(current);
        match_sum(ans, current, root->left, sum - root->val);
        match_sum(ans, current, root->right, sum - root->val);
        current.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> ans;
        vector<int> current;
        match_sum(ans, current, root, sum);
        return ans;
    }
};
