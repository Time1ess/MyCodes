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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(!root) {
            return {};
        }
        queue<TreeNode*> q;
        q.push(root);
        vector<vector<int>> ans;
        while(!q.empty()) {
            vector<int> cur;
            queue<TreeNode*> next;
            while(!q.empty()) {
                auto front = q.front();
                q.pop();
                cur.push_back(front->val);
                if(front->left) {
                    next.push(front->left);
                }
                if(front->right) {
                    next.push(front->right);
                }
            }
            ans.push_back(cur);
            q = next;
        }
        return ans;
    }
};
