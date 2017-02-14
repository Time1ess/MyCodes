// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-14 08:29
// Last modified: 2017-02-14 08:29
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
    void update_values(TreeNode* root, int depth, vector<int> &v)
    {
        if(root == NULL)
            return;
        if(v.size() < depth+1)
        {
            v.resize(depth+1);
            v[depth] = root->val;
        }
        else
        {
            v[depth] = max(root->val, v[depth]);
        }
        update_values(root->left, depth+1, v);
        update_values(root->right, depth+1, v);
    }
    vector<int> largestValues(TreeNode* root) {
        vector<int> result;
        update_values(root, 0, result);
        return result;
    }
};
