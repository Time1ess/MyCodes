// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-05 08:26
// Last modified: 2017-06-05 08:26
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
    void build_str(TreeNode *t, string &s)
    {
        if(t == NULL)
            return;
        s += to_string(t->val);
        if(t->right || t->left)
        {
            s += "(";
            build_str(t->left, s);
            s += ")";
        }
        if(t->right)
        {
            s += "(";
            build_str(t->right, s);
            s += ")";
        }
    }
    string tree2str(TreeNode* t) {
        string s;
        build_str(t, s);
        return s;
    }
};
