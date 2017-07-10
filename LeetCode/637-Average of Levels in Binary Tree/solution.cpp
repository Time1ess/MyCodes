// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-10 09:13
// Last modified: 2017-07-10 09:13
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
    void dfs(TreeNode* root, vector<long> &sums, vector<int> &cnts, int level)
    {
        if(root == NULL)
            return;
        if(level >= sums.size())
        {
            sums.push_back(root->val);
            cnts.push_back(1);
        }
        else
        {
            sums[level] += root->val;
            cnts[level] ++;
        }
        dfs(root->left, sums, cnts, level+1);
        dfs(root->right, sums, cnts, level+1);
    }
    vector<double> averageOfLevels(TreeNode* root) {
        vector<long> sums;
        vector<int> cnts;
        dfs(root, sums, cnts, 0);
        vector<double> ans;
        for(int i = 0; i < sums.size(); i++)
            ans.push_back(1.0 * sums[i] / cnts[i]);
        return ans;
    }
};
