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
    void findBottomLeftValue(TreeNode* root, int& ans, int& ans_depth, int depth) {
        if (root == nullptr) {
            return;
        }
        findBottomLeftValue(root->right, ans, ans_depth, depth + 1);
        if (depth >= ans_depth) {
            ans_depth = depth;
            ans = root->val;
        }
        findBottomLeftValue(root->left, ans, ans_depth, depth + 1);
    }
    int findBottomLeftValue(TreeNode* root) {
        int ans = 0;
        int ans_depth = -1;
        findBottomLeftValue(root, ans, ans_depth, 0);
        return ans;
    }
};
