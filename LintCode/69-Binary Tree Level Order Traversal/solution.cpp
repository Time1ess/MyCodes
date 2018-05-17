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
     * @return: Level order a list of lists of integer
     */
    vector<vector<int>> levelOrder(TreeNode * root) {
        // write your code here
        if(!root)
            return {};
        queue<TreeNode*> level;
        vector<vector<int>> ans;
        level.push(root);
        while(!level.empty())
        {
            vector<int> current;
            queue<TreeNode*> next_level;
            while(!level.empty())
            {
                TreeNode* node = level.front();
                level.pop();
                current.push_back(node->val);
                if(node->left)
                    next_level.push(node->left);
                if(node->right)
                    next_level.push(node->right);
            }
            ans.push_back(current);
            level = next_level;
        }
        return ans;
    }
};
