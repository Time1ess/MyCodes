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
     * @param root: the given BST
     * @param target: the given target
     * @param k: the given k
     * @return: k values in the BST that are closest to the target
     */
    vector<int> closestKValues(TreeNode * root, double target, int k) {
        // write your code here
        stack<TreeNode*> prev, next;
        TreeNode *node = root;
        while(node)
        {
            if(node->val < target)
            {
                prev.push(node);
                node = node->right;
            }
            else
            {
                next.push(node);
                node = node->left;
            }
        }
        vector<int> ans;
        for(int i = 0; i < k; i++)
        {
            if(prev.empty() ||
               !next.empty() && next.top()->val - target < target - prev.top()->val)
            {
                ans.push_back(next.top()->val);
                go_next(next);
            }
            else
            {
                ans.push_back(prev.top()->val);
                go_prev(prev);
            }
        }
        return ans;
    }
    void go_next(stack<TreeNode*> &next)
    {
        TreeNode *node = next.top()->right;
        next.pop();
        while(node)
        {
            next.push(node);
            node = node->left;
        }
    }
    void go_prev(stack<TreeNode*> &prev)
    {
        TreeNode *node = prev.top()->left;
        prev.pop();
        while(node)
        {
            prev.push(node);
            node = node->right;
        }
    }
};
