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
        if(root == NULL)
            return ans;
        stack<TreeNode *> s;
        TreeNode *current = root;
        while(!s.empty() || current)
        {
            if(current)
            {
                s.push(current);
                current = current->left;
            }
            else
            {
                current = s.top();
                s.pop();
                ans.push_back(current->val);
                current = current->right;
            }
        }
        return ans;
    }
};
