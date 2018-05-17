/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */

class Solution {
public:
    /**
     * @param root: A Tree
     * @return: Preorder in ArrayList which contains node values.
     */
    vector<int> preorderTraversal(TreeNode * root) {
        // write your code here
        if(!root)
            return {};
        vector<int> ans;
        while(root)
        {
            if(root->left)
            {
                TreeNode *next = root->left;
                while(next->right && next->right != root)
                    next = next->right;
                if(next->right == NULL)
                {
                    ans.push_back(root->val);
                    next->right = root;
                    root = root->left;
                }
                else
                {
                    next->right = NULL;
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
