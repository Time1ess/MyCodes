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
    void traverse(TreeNode* root, int& greater_sum) {
        if(!root) {
            return;
        }
        traverse(root->right, greater_sum);
        root->val += greater_sum;
        greater_sum = root->val;
        traverse(root->left, greater_sum);
    }
    TreeNode* convertBST(TreeNode* root) {
        int greater_sum = 0;
        traverse(root, greater_sum);
        return root;
    }
};
