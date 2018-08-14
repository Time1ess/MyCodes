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
    TreeNode* buildTree(vector<int>& preorder, int ps, int pe, vector<int>& inorder, int is, int ie) {
        if (ps > pe || is > ie) {
            return NULL;
        }
        TreeNode* root = new TreeNode(preorder[ps]);
        if (ps == pe) {
            return root;
        }
        int idx = find(inorder.begin() + is, inorder.begin() + ie, root->val) - inorder.begin();
        root->left = buildTree(preorder, ps + 1, ps + idx - is, inorder, is, idx - 1);
        root->right = buildTree(preorder, ps + idx - is + 1, pe, inorder, idx + 1, ie);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        if (n == 0) {
            return NULL;
        }
        return buildTree(preorder, 0, n - 1, inorder, 0, n - 1);
    }
};
