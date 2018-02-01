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
    /*
     * @param root: the root of the binary tree
     * @return: all root-to-leaf paths
     */
    vector<string> binaryTreePaths(TreeNode * root) {
        // write your code here
        vector<string> ans;
        if(!root)
            return ans;
        stack<pair<TreeNode*, string>> s;
        s.push({root, ""});
        while(!s.empty())
        {
            pair<TreeNode*, string> top = s.top();
            s.pop();
            TreeNode* node = top.first;
            string &current = top.second;
            current += to_string(node->val);
            if(node->left == NULL && node->right == NULL)
            {
                ans.push_back(current);
                continue;
            }
            current += "->";
            if(node->left)
                s.push({node->left, current});
            if(node->right)
                s.push({node->right, current});
        }
        return ans;
    }
};
