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
    TreeNode* buildTree(vector<int> &preorder, vector<int> &inorder, int lp, int rp, int li, int ri)
    {
        if(lp == rp)
            return NULL;
        TreeNode *root = new TreeNode(preorder[lp]);
        if(rp - lp == 1)
            return root;
        int idx = li;
        for(; idx < ri; idx++)
            if(inorder[idx] == preorder[lp])
                break;
        root->left = buildTree(preorder, inorder, lp + 1, lp + 1 + idx - li, li, idx);
        root->right = buildTree(preorder, inorder, lp + 1 + idx - li, rp, idx + 1, ri);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        return buildTree(preorder, inorder, 0, n, 0, n);
    }
};
