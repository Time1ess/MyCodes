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
        while(root)
        {
            if(root->left)
            {
                TreeNode* pre = root->left;
                while(pre->right && pre->right != root)
                    pre = pre->right;
                if(pre->right == NULL)
                {
                    ans.push_back(root->val);
                    pre->right = root;
                    root = root->left;
                }
                else
                {
                    pre->right = NULL;
                    root = root->right;
                }
            }
            else
            {
                ans.push_back(root->val);
                root = root->right;
            }
        }
        return ans;
    }
};
