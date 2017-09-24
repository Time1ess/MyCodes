// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-24 10:56
// Last modified: 2017-09-24 10:56
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
    vector<TreeNode*> build_trees(int left, int right)
    {
        vector<TreeNode*> ans;
        if(left > right)
        {
            ans.push_back(NULL);
            return ans;
        }
        else if(left == right)
        {
            ans.push_back(new TreeNode(left));
            return ans;
        }
        for(int i = left; i <= right; i++)
        {
            vector<TreeNode*> left_trees = build_trees(left, i - 1);
            vector<TreeNode*> right_trees = build_trees(i + 1, right);
            for(int il = 0; il < left_trees.size(); il++)
                for(int ir = 0; ir < right_trees.size(); ir++)
                {
                    TreeNode *root = new TreeNode(i);
                    root->left = left_trees[il];
                    root->right = right_trees[ir];
                    ans.push_back(root);
                }
        }
        return ans;
    }
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> ans;
        if(n == 0)
            return ans;
        ans = build_trees(1, n);
        return ans;
    }
};
