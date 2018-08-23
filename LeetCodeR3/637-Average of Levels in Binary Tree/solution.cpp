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
    void generate_levels(TreeNode* root, vector<vector<int>>& levels, int level) {
        if (root == nullptr) {
            return;
        }
        if (levels.size() == level) {
            levels.push_back({});
        }
        levels[level].push_back(root->val);
        generate_levels(root->left, levels, level + 1);
        generate_levels(root->right, levels, level + 1);
    }
    vector<double> averageOfLevels(TreeNode* root) {
        vector<vector<int>> levels;
        generate_levels(root, levels, 0);
        vector<double> ans;
        for (auto level: levels) {
            double sum = 0;
            for (auto x: level) {
                sum += x;
            }
            ans.push_back(sum / level.size());
        }
        return ans;
    }
};
