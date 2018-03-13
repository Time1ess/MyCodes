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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        if(!root)
            return ans;
        TreeNode* last = NULL;
        stack<TreeNode *> s;
        s.push(root);
        while(!s.empty())
        {
            TreeNode *node = s.top();
            if((node->left == NULL && node->right == NULL)
                    || (last && (node->left == last || node->right == last)))
            {
                ans.push_back(node->val);
                s.pop();
                last = node;
            }
            else
            {
                if(node->right)
                    s.push(node->right);
                if(node->left)
                    s.push(node->left);
            }
        }
        return ans;
    }
};
