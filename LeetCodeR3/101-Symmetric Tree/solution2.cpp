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
    bool isSymmetric(TreeNode* root) {
        if(root == nullptr) {
            return true;
        }
        queue<pair<TreeNode*, TreeNode*>> q;
        q.push({root->left, root->right});
        while(!q.empty()) {
            auto front = q.front();
            q.pop();
            TreeNode* t1 = front.first;
            TreeNode* t2 = front.second;
            if(t1 == nullptr && t2 == nullptr) {
                continue;
            } else if(t1 == nullptr || t2 == nullptr || t1->val != t2->val) {
                return false;
            }
            q.push({t1->left, t2->right});
            q.push({t1->right, t2->left});
        }
        return true;
    }
};
