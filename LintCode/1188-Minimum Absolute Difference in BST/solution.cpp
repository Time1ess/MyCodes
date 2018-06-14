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
     * @return: the minimum absolute difference between values of any two nodes
     */
    void inOrderTraverse(TreeNode* root, long long& min_diff, long long& last_val) {
        if(!root)
            return;
        inOrderTraverse(root->left, min_diff, last_val);
        min_diff = min(min_diff, root->val - last_val);
        last_val = root->val;
        inOrderTraverse(root->right, min_diff, last_val);
    }
    int getMinimumDifference(TreeNode * root) {
        // Write your code here
        if(!root)
            return 0;
        long long min_diff = INT_MAX, last_val = INT_MIN;
        inOrderTraverse(root, min_diff, last_val);
        return min_diff;
    }
};
