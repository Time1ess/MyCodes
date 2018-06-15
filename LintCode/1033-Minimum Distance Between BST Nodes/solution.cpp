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
     * @param root: the root
     * @return: the minimum difference between the values of any two different nodes in the tree
     */
    void minDiffInBST(TreeNode* root, long long& ans, long long& lastVal) {
        if(!root)
            return;
        minDiffInBST(root->left, ans, lastVal);
        ans = min(ans, root->val - lastVal);
        lastVal = root->val;
        minDiffInBST(root->right, ans, lastVal);
    }
    int minDiffInBST(TreeNode * root) {
        // Write your code here
        if(!root)
            return 0;
        long long lastVal = INT_MIN;
        long long ans = INT_MAX;
        minDiffInBST(root, ans, lastVal);
        return ans;
    }
};
