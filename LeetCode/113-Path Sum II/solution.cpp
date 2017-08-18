// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-18 08:44
// Last modified: 2017-08-18 08:44
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
        else if(root->left == NULL && root->right == NULL && root->val == sum)
        {
            current.push_back(root->val);
            ans.push_back(current);
            current.pop_back();
            return;
        }
        current.push_back(root->val);
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
