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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        while (root) {
            if (root->left) {
                TreeNode* node = root->left;
                while (node->right != nullptr && node->right != root) {
                    node = node->right;
                }
                if (node->right == nullptr) {
                    ans.push_back(root->val);
                    node->right = root;
                    root = root->left;
                } else {
                    node->right = nullptr;
                    root = root->right;
                }
            } else {
                ans.push_back(root->val);
                root = root->right;
            }
        }
        return ans;
    }
};
