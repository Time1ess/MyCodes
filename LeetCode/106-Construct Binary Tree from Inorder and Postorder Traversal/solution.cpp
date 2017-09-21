// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-21 08:46
// Last modified: 2017-09-21 08:46
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
    TreeNode* build_tree(vector<int> &inorder, vector<int>& postorder, int& root_idx, int left, int right)
    {
        if(left >= right)
            return NULL;
        root_idx--;
        TreeNode* root = new TreeNode(postorder[root_idx]);
        
        int split;
        for(int i = left; i < right; i++)
            if(inorder[i] == postorder[root_idx])
            {
                split = i;
                break;
            }
        
        root->right = build_tree(inorder, postorder, root_idx, split+1, right);
        root->left = build_tree(inorder, postorder, root_idx, left, split);

        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int size = inorder.size();
        return build_tree(inorder, postorder, size, 0, size);
    }
};
