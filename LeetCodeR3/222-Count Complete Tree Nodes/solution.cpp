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
    int get_height(TreeNode* root) {
        return root == nullptr ? -1 : 1 + get_height(root->left);
    }
    int countNodes(TreeNode* root) {
        int height = get_height(root);
        return height == -1 ?
            0 : get_height(root->right) == height - 1 ? 
                (1 << height) + countNodes(root->right) : (1 << (height - 1)) + countNodes(root->left);
    }
};
