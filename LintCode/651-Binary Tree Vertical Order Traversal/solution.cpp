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
     * @param root: the root of tree
     * @return: the vertical order traversal
     */
    vector<vector<int>> verticalOrder(TreeNode * root) {
        // write your code here
        if(!root) {
            return {};
        }
        map<int, vector<int>> levels;
        vector<vector<int>> ans;
        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});
        while(!q.empty()) {
            auto front = q.front();
            q.pop();
            TreeNode* node = front.first;
            int level = front.second;
            levels[level].push_back(node->val);
            if(node->left) {
                q.push({node->left, level-1});
            }
            if(node->right) {
                q.push({node->right, level+1});
            }
        }
        for(auto p: levels) {
            ans.push_back(p.second);
        }
        return ans;
    }
};
