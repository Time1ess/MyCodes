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
     * @param root: the given BST
     * @param k: the given k
     * @return: the kth smallest element in BST
     */
    void in_order(TreeNode *root, int &ans, int &cnt, int k)
    {
        if(!root)
            return;
        in_order(root->left, ans, cnt, k);
        if(cnt == k)
            return;
        cnt++;
        if(cnt == k)
        {
            ans = root->val;
            return;
        }
        in_order(root->right, ans, cnt, k);
    }
    int kthSmallest(TreeNode * root, int k) {
        // write your code here
        int cnt = 0, ans;
        in_order(root, ans, cnt, k);
        return ans;
    }
};
