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
    void Mirror(TreeNode *pRoot) {
        if(!pRoot)
            return;
        queue<TreeNode *> q;
        q.push(pRoot);
        while(!q.empty())
        {
            TreeNode *tmp = q.front();
            q.pop();
            if(tmp->left)
                q.push(tmp->left);
            if(tmp->right)
                q.push(tmp->right);
            TreeNode *tmp_swap;
            tmp_swap = tmp->left;
            tmp->left = tmp->right;
            tmp->right = tmp_swap;
        }
    }
};
