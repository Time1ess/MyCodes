// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-14 11:00
// Last modified: 2017-04-14 11:00
// Filename: solution2.cpp
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
    void pre_order(TreeNode *root, vector<string> &ans, vector<int> &cur)
    {
        cur.push_back(root->val);
        if(root->left)
            pre_order(root->left, ans, cur);
        if(root->right)
            pre_order(root->right, ans, cur);
        if(!root->left && !root->right && cur.size() != 0)
        {
            stringstream ss;
            for(int i = 0; i < cur.size(); i++)
            {
                if(i != 0)
                    ss<<"->";
                ss<<cur[i];
            }
            ans.push_back(ss.str());
        }
        cur.pop_back();
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> ans;
        if(root == NULL)
            return ans;
        vector<int> cur;
        pre_order(root, ans, cur);
        return ans;
    }
};
