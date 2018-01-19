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
    vector<int> PrintFromTopToBottom(TreeNode* root) {
		vector<int> ans;
        if(!root)
            return ans;
        queue<TreeNode *> q;
        q.push(root);
        while(!q.empty())
        {
            TreeNode* tmp = q.front();
            q.pop();
            ans.push_back(tmp->val);
            if(tmp->left)
                q.push(tmp->left);
            if(tmp->right)
                q.push(tmp->right);
        }
        return ans;
    }
};
