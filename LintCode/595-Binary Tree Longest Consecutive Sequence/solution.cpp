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
     * @param root: the root of binary tree
     * @return: the length of the longest consecutive sequence path
     */
    int longestConsecutive(TreeNode* root, int& ans, int target) {
        if(!root)
            return 0;
        int left = longestConsecutive(root->left, ans, root->val + 1);
        int right = longestConsecutive(root->right, ans, root->val + 1);
        ans = max(ans, max(left, right) + 1);
        if(root->val == target)
            return max(left, right) + 1;
        return 0;
    }
    int longestConsecutive(TreeNode * root) {
        // write your code here
        if(!root)
            return 0;
        int ans = 0;
        longestConsecutive(root, ans, root->val + 1);
        return ans;
    }
};
