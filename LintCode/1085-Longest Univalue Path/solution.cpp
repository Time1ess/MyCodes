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
     * @param root: 
     * @return: the length of the longest path where each node in the path has the same value
     */
    int longestUnivalueNodes(TreeNode* root, int& ans, int val) {
        if(!root)
            return 0;
        int left = longestUnivalueNodes(root->left, ans, root->val);
        int right = longestUnivalueNodes(root->right, ans, root->val);
        ans = max(ans, left + right);
        if(root->val == val)
            return max(left, right) + 1;
        return 0;
    }
    int longestUnivaluePath(TreeNode * root) {
        if(!root)
            return 0;
        int ans = 0;
        longestUnivalueNodes(root, ans, 0);
        return ans;
    }
};
