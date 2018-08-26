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
    void kthSmallest(TreeNode* root, int& ans, int& cur, int k) {
        if (root == nullptr) {
            return;
        }
        kthSmallest(root->left, ans, cur, k);
        if (cur == k) {
            return;
        }
        if (++cur == k) {
            ans = root->val;
            return;
        }
        kthSmallest(root->right, ans, cur, k);
    }
    int kthSmallest(TreeNode* root, int k) {
        int cur = 0;
        int ans = 0;
        kthSmallest(root, ans, cur, k);
        return ans;
    }
};
