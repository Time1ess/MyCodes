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
    int maxDepth(TreeNode* root) {
        int rightlen=1;
        int leftlen=1;
        if(root==NULL)
            return 0;
        if(root->left)
         leftlen+=maxDepth(root->left);
        if(root->right)
         rightlen+=maxDepth(root->right);
        return leftlen>rightlen?leftlen:rightlen;
        
    }
};
