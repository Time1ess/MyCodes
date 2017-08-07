// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-07 09:55
// Last modified: 2017-08-07 09:55
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
    int max_depth(TreeNode* root)
    {
        if(root == NULL)
            return 0;
        return max(max_depth(root->left), max_depth(root->right)) + 1;
    }
    void FillTree(vector<vector<string>> &tree, TreeNode* root, int depth, int left, int right)
    {
        if(root == NULL)
            return;
        int mid = (left + right) / 2;
        tree[depth][mid] = to_string(root->val);
        FillTree(tree, root->left, depth+1, left, mid);
        FillTree(tree, root->right, depth+1, mid+1, right);
    }
    vector<vector<string>> printTree(TreeNode* root) {
        int depth = max_depth(root);
        int width = pow(2, depth)-1;
        vector<vector<string>> tree(depth, vector<string>(width, ""));
        FillTree(tree, root, 0, 0, width);
        return tree;
    }
};
