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
    void rootToLeafSum(TreeNode* root, int& ans, int cur) {
        if (root == nullptr) {
            return;
        } else if (root->left == nullptr && root->right == nullptr) {
            ans += cur * 10 + root->val;
        } else {
            rootToLeafSum(root->left, ans, cur * 10 + root->val);
            rootToLeafSum(root->right, ans, cur * 10 + root->val);
        }
    }
    int sumNumbers(TreeNode* root) {
        int ans = 0;
        rootToLeafSum(root, ans, 0);
        return ans;
    }
};
