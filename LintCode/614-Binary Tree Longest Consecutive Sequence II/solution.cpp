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
    int longestConsecutive(TreeNode* root, int& ans, int target, int delta) {
        if(!root || root->val != target) {
            return 0;
        }
        int left_asc = longestConsecutive(root->left, ans, target + 1, 1);
        int left_desc = longestConsecutive(root->left, ans, target - 1, -1);
        int right_asc = longestConsecutive(root->right, ans, target + 1, 1);
        int right_desc = longestConsecutive(root->right, ans, target - 1, -1);
        ans = max(ans, left_asc + 1 + right_desc);
        ans = max(ans, right_asc + 1 + left_desc);
        return 1 + (delta == 1 ? max(left_asc, right_asc) : max(left_desc, right_desc));
    }
    /**
     * @param root: the root of binary tree
     * @return: the length of the longest consecutive sequence path
     */
    int longestConsecutive2(TreeNode * root) {
        // write your code here
        if(!root) {
            return 0;
        }
        int ans = 0;
        longestConsecutive(root, ans, root->val, 1);
        return max(ans, max(longestConsecutive2(root->left),
                            longestConsecutive2(root->right)));
    }
};
