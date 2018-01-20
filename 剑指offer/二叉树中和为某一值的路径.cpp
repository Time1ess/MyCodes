/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
    void find_expect_number_path(vector<vector<int>> &ans, vector<int> &current,
                                 TreeNode* root, int expectNumber)
    {
        if(!root || root->val > expectNumber)
            return;
        else if(root->val == expectNumber && !root->left && !root->right)
        {
            current.push_back(root->val);
            ans.push_back(current);
            current.pop_back();
            return;
        }
        else if(root->val < expectNumber)
        {
            current.push_back(root->val);
            find_expect_number_path(ans, current, root->left, expectNumber - root->val);
            find_expect_number_path(ans, current, root->right, expectNumber - root->val);
            current.pop_back();
        }
    }
    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
		vector<vector<int>> ans;
        if(!root)
            return ans;
        vector<int> current;
        find_expect_number_path(ans, current, root, expectNumber);
        return ans;
    }
};
