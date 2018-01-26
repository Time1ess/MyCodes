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
        if(pRoot == NULL)
            return ans;
        deque<TreeNode *> l2r, r2l;
        vector<int> tmp_vec;
        TreeNode *tmp;
        l2r.push_back(pRoot);
        while(!l2r.empty() || !r2l.empty())
        {
            if(!l2r.empty())
            {
                while(!l2r.empty())
                {
                    tmp = l2r.front();
                    l2r.pop_front();
                    tmp_vec.push_back(tmp->val);
                    if(tmp->left)
                        r2l.push_back(tmp->left);
                    if(tmp->right)
                        r2l.push_back(tmp->right);
                }
                ans.push_back(tmp_vec);
                tmp_vec.clear();
            }
            if(!r2l.empty())
            {
                while(!r2l.empty())
                {
                    tmp = r2l.back();
                    r2l.pop_back();
                    tmp_vec.push_back(tmp->val);
                    if(tmp->right)
                        l2r.push_front(tmp->right);
                    if(tmp->left)
                        l2r.push_front(tmp->left);
                }
                ans.push_back(tmp_vec);
                tmp_vec.clear();
            }
        }
        return ans;
    }
    
};
