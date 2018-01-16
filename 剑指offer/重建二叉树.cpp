/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* re_construct(vector<int> &pre, vector<int> &vin, int pre_s, int pre_e, int vin_s, int vin_e)
    {
        if(pre_s >= pre_e || vin_s >= vin_e)
            return NULL;
        TreeNode* root = new TreeNode(pre[pre_s]);
        int k = vin_s;
        while(vin[k] != pre[pre_s])
            k++;
        root->left = re_construct(pre, vin, pre_s + 1, pre_s + 1 + k - vin_s, vin_s, k);
        root->right = re_construct(pre, vin, pre_s + 1 + k - vin_s, pre_e, k + 1, vin_e);
        return root;
    }
    
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
		return re_construct(pre, vin, 0, pre.size(), 0, vin.size());
    }
};
