// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-15 09:55
// Last modified: 2017-09-15 09:55
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
    string build_tree(vector<TreeNode*> &ans, unordered_map<string, int> &duplicates, TreeNode *root)
    {
        if(!root)
            return "";
        string s = to_string(root->val);
        if(root->left)
            s += build_tree(ans, duplicates, root->left);
        else
            s += "#";
        if(root->right)
            s += build_tree(ans, duplicates, root->right);
        else
            s += "#";
        if(duplicates.find(s) != duplicates.end() && duplicates[s] == 1)
            ans.push_back(root);
        duplicates[s]++;
        return s;
    }
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        unordered_map<string, int> duplicates;
        vector<TreeNode*> ans;
        build_tree(ans, duplicates, root);
        return ans;
    }
};
