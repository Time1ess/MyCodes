class Solution {
public:
    bool IsBalanced(TreeNode* root, int &depth)
    {
        if(!root)
        {
            depth = 0;
            return true;
        }
        int left, right;
        if(IsBalanced(root->left, left) && IsBalanced(root->right, right))
        {
            int diff = left - right;
            if(diff <= 1 && diff >= -1)
            {
                depth = max(left, right) + 1;
                return true;
            }
        }
        return false;
    }
    bool IsBalanced_Solution(TreeNode* pRoot) {
		int depth = 0;
        return IsBalanced(pRoot, depth);
    }
};
