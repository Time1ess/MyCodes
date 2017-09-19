// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-19 09:26
// Last modified: 2017-09-19 09:26
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
    TreeNode* build_tree(vector<int>& preorder, int& start, vector<int>& inorder, int left, int right)
    {
        if(left >= right)
            return NULL;
        TreeNode* root = new TreeNode(preorder[start]);
        int split = left;
        while(split < right)
            if(preorder[start] == inorder[split])
                break;
            else
                split++;
        start++;
        root->left = build_tree(preorder, start, inorder, left, split);
        root->right = build_tree(preorder, start, inorder, split+1, right);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.size() == 0 || inorder.size() == 0)
            return NULL;
        int start = 0;
        return build_tree(preorder, start, inorder, 0, inorder.size());
    }
};
