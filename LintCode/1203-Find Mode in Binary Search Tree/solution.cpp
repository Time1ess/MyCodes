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
     * @param root: a root of integer
     * @return: return a integer
     */
    void findMode(TreeNode* root, vector<int>& vals, int& val, int &cnt, int& max_cnt) {
        if (!root)
            return;
        findMode(root->left, vals, val, cnt, max_cnt);
        if (val == root->val)
            cnt++;
        else {
            if (cnt > max_cnt) {
                max_cnt = cnt;
                vals.clear();
                vals.push_back(val);
            } else if (cnt == max_cnt) {
                vals.push_back(val);
            }
            cnt = 1;
            val = root->val;
        }
        findMode(root->right, vals, val, cnt, max_cnt);
    }
    vector<int> findMode(TreeNode * root) {
        if (!root)
            return {};
        // write your code here
        vector<int> vals;
        int val = INT_MIN;
        int cnt = 0;
        int max_cnt = 0;
        findMode(root, vals, val, cnt, max_cnt);
        if (cnt > max_cnt) {
            vals.clear();
            vals.push_back(val);
        } else if(cnt == max_cnt) {
            vals.push_back(val);
        }
        return vals;
    }
};
