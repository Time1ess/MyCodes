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
    bool isSameTree(TreeNode* s, TreeNode* t) {
        if(s == nullptr && t == nullptr) {
            return true;
        } else if(s == nullptr || t == nullptr) {
            return false;
        }
        return s->val == t->val && isSameTree(s->left, t->left) && isSameTree(s->right, t->right);
    }
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if(t == nullptr) {
            return true;
        } else if(s == nullptr) {
            return false;
        }
        return isSameTree(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t);
    }
};
