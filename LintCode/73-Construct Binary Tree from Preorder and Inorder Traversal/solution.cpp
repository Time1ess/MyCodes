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
     * @param inorder: A list of integers that inorder traversal of a tree
     * @param postorder: A list of integers that postorder traversal of a tree
     * @return: Root of a tree
     */
    TreeNode* buildTree(vector<int> &pre, int pre_s, int pre_e,
                        vector<int> &in, int in_s, int in_e)
    {
        if(pre_s >= pre_e)
            return NULL;
        TreeNode* root = new TreeNode(pre[pre_s]);
        int in_m = in_s;
        while(in_m < in_e && in[in_m] != pre[pre_s])
            in_m++;
        int cnt = in_m - in_s;
        root->left = buildTree(pre, pre_s + 1, pre_s + 1 + cnt, in, in_s, in_m);
        root->right = buildTree(pre, pre_s + 1 + cnt, pre_e, in, in_m + 1, in_e);
        return root;
    }
    TreeNode * buildTree(vector<int> &preorder, vector<int> &inorder) {
        // write your code here
        int n = preorder.size();
        return buildTree(preorder, 0, n, inorder, 0, n);
    }
};
