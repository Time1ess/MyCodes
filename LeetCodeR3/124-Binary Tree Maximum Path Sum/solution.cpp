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
    long long maxPathSum(TreeNode* root, long long& ans) {
        if (root == nullptr) {
            return 0;
        }
        long long left = maxPathSum(root->left, ans);
        long long right = maxPathSum(root->right, ans);
        if (left < 0) {
            left = 0;
        }
        if (right < 0) {
            right = 0;
        }
        ans = max(ans, left + root->val + right);
        return root->val + max(left, right);
    }
    int maxPathSum(TreeNode* root) {
        long long ans = INT_MIN;
        maxPathSum(root, ans);
        return ans;
    }
};
