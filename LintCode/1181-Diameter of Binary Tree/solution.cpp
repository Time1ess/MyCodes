/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */

class Solution {
public:
    /**
     * @param root: a root of binary tree
     * @return: return a integer
     */
    int diameterOfBinaryTree(TreeNode * root) {
        // write your code here
        int ans = 0;
        int depth = diameterWithDepth(root, ans);
        return ans;
    }
    int diameterWithDepth(TreeNode* root, int& ans) {
        if (!root) {
            return 0;
        }
        int left_depth = diameterWithDepth(root->left, ans);
        int right_depth = diameterWithDepth(root->right, ans);
        ans = max(ans, left_depth + right_depth);
        return max(left_depth, right_depth) + 1;
    }
};
