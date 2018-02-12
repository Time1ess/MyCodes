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
    TreeNode* addOneRow(TreeNode* root, int v, int d, bool as_left)
    {
        if(!root)
        {
            if(d == 1)
                root = new TreeNode(v);
            return root;
        }
        if(d == 1)
        {
            TreeNode* node = new TreeNode(v);
            if(as_left)
                node->left = root;
            else
                node->right = root;
            return node;
        }
        root->left = addOneRow(root->left, v, d - 1, true);
        root->right = addOneRow(root->right, v, d - 1, false);
        return root;
    }
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        return addOneRow(root, v, d, true);
    }
};
