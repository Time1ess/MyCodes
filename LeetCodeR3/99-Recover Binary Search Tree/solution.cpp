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
    TreeNode* find_wrong_node(TreeNode* root, TreeNode** last) {
        if (root == nullptr) {
            return root;
        }
        TreeNode* right = find_wrong_node(root->right, last);
        if (right != nullptr) {
            return right;
        }
        if (*last != nullptr && root->val > (*last)->val) {
            return *last;
        }
        *last = root;
        return find_wrong_node(root->left, last);
    }
    TreeNode* find_fix_node(TreeNode* root, int v) {
        if (root == nullptr) {
            return root;
        }
        TreeNode* left = find_fix_node(root->left, v);
        if (left != nullptr) {
            return left;
        }
        if (root->val > v) {
            return root;
        }
        return find_fix_node(root->right, v);
    }
    void recoverTree(TreeNode* root) {
        // Find wrong node
        // case: [INT_MAX, 1, 2, 3, 4]
        if (root == nullptr) {
            return;
        }
        TreeNode* last = nullptr;
        TreeNode* wrong = find_wrong_node(root, &last);
        TreeNode* fix = find_fix_node(root, wrong->val);
        swap(wrong->val, fix->val);
    }
};
