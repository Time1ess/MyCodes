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
     * @param root: param root: The root of the binary search tree
     * @param k1: An integer
     * @param k2: An integer
     * @return: return: Return all keys that k1<=key<=k2 in ascending order
     */
    void in_order(TreeNode *root, vector<int> &ans, int k1, int k2)
    {
        if(!root)
            return;
        if(root->val > k1)
            in_order(root->left, ans, k1, k2);
        if(root->val >= k1 && root->val <= k2)
            ans.push_back(root->val);
        if(root->val < k2)
            in_order(root->right, ans, k1, k2);
    }
    vector<int> searchRange(TreeNode * root, int k1, int k2) {
        // write your code here
        vector<int> ans;
        in_order(root, ans, k1, k2);
        return ans;
    }
};
