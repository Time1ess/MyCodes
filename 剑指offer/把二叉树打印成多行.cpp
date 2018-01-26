/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
*/
class Solution {
public:
    vector<vector<int> > Print(TreeNode* pRoot) {
    	vector<vector<int>> ans;
        if(!pRoot)
            return ans;
        int waiting_print = 0;
        int next_waiting = 0;
        queue<TreeNode *> q;
        q.push(pRoot);
        waiting_print++;
        vector<int> row;
        while(!q.empty())
        {
            TreeNode* tmp = q.front();
            q.pop();
            if(tmp->left)
            {
                q.push(tmp->left);
                next_waiting++;
            }
            if(tmp->right)
            {
                q.push(tmp->right);
                next_waiting++;
            }
            row.push_back(tmp->val);
            waiting_print --;
            if(waiting_print == 0)
            {
                ans.push_back(row);
                row.clear();
                waiting_print = next_waiting;
                next_waiting = 0;
            }
        }
        return ans;
    }
};
