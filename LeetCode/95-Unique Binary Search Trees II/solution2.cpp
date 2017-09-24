// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-24 11:21
// Last modified: 2017-09-24 11:21
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
    TreeNode* clone(TreeNode *root)
    {
        if(root == NULL)
            return NULL;
        TreeNode* new_root = new TreeNode(root->val);
        new_root->left = clone(root->left);
        new_root->right = clone(root->right);
        return new_root;
    }
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> ans;
        if(n == 0)
            return ans;
        
        ans.push_back(NULL);
        for(int i = 1; i <= n; i++)
        {
            vector<TreeNode*> tmp;
            for(int j = 0; j < ans.size(); j++)
            {
                TreeNode* root = ans[j];
                TreeNode* new_node = new TreeNode(i);
                new_node->left = root;  // Insert i as new root
                tmp.push_back(clone(new_node));
                
                if(root != NULL)
                {
                    TreeNode* tmp_root = root;  // Insert i to right sub-tree
                    while(tmp_root->right != NULL)
                    {
                        TreeNode* next_right = tmp_root->right;
                        tmp_root->right = new_node;
                        new_node->left = next_right;
                        tmp.push_back(clone(root));
                        
                        // Restore
                        tmp_root->right = next_right;
                        tmp_root = tmp_root->right;
                    }
                    tmp_root->right = new TreeNode(i);
                    tmp.push_back(clone(root));
                }
            }
            ans = tmp;
        }
        return ans;
    }
};
