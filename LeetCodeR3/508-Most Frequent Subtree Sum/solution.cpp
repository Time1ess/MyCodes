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
    int find_subtree_sum(TreeNode* root, unordered_map<int, int>& cnts) {
        if (root == nullptr) {
            return 0;
        }
        int v = root->val + find_subtree_sum(root->left, cnts) + find_subtree_sum(root->right, cnts);
        cnts[v]++;
        return v;
    }
    vector<int> findFrequentTreeSum(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }
        unordered_map<int, int> cnts;
        find_subtree_sum(root, cnts);
        vector<int> ans;
        int max_cnt = 0;
        for (auto p : cnts) {
            if (p.second >= max_cnt) {
                if (p.second > max_cnt) {
                    ans.clear();
                    max_cnt = p.second;
                }
                ans.push_back(p.first);
            }
        }
        return ans;
    }
};
