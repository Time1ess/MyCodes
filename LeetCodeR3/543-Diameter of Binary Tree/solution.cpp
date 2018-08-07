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
    int getLength(TreeNode* root, int& ans) {
        if(!root) {
            return 0;
        }
        int left = getLength(root->left, ans);
        int right = getLength(root->right, ans);
        ans = max(ans, left + right);
        return max(left, right) + 1;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        int ans = 0;
        int len = getLength(root, ans);
        return max(len - 1, ans);
    }
};
