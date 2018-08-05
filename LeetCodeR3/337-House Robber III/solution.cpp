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
    /* Params:
     *   child_sum: Max rob sum without root.
     */
    int rob(TreeNode* root, int& child_sum) {
        if(!root) {
            child_sum = 0;
            return 0;
        }
        int left_child, right_child;
        int left = rob(root->left, left_child);
        int right = rob(root->right, right_child);
        child_sum = left + right;
        return max(root->val + left_child + right_child, left + right);
    }
    int rob(TreeNode* root) {
        int child_sum = 0;
        return rob(root, child_sum);
    }
};
