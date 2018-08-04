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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        while(root) {
            if(root->left) {
                TreeNode* next = root->left;
                while(next->right && next->right != root) {
                    next = next->right;
                }
                if(next->right == root) {
                    next->right = NULL;
                    ans.push_back(root->val);
                    root = root->right;
                } else {
                    next->right = root;
                    root = root->left;
                }
            } else {
                ans.push_back(root->val);
                root = root->right;
            }
        }
        return ans;
    }
};
