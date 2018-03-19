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
 
double t;

double diff(int v)
{
    return abs(v - t);
}

struct Compare{
    bool operator()(const int &a, const int &b)
    {
        return diff(a) < diff(b);
    }
};

class Solution {
public:
    /**
     * @param root: the given BST
     * @param target: the given target
     * @param k: the given k
     * @return: k values in the BST that are closest to the target
     */
    void find_closest(TreeNode *root,
                      priority_queue<int, vector<int>, Compare> &pq, int k)
    {
        if(!root)
            return;
        find_closest(root->left, pq, k);
        if(pq.size() < k)
            pq.push(root->val);
        else if((pq.size() == k && diff(root->val) < diff(pq.top())))
        {
            pq.pop();
            pq.push(root->val);
        }
        find_closest(root->right, pq, k);
    }
    
    vector<int> closestKValues(TreeNode * root, double target, int k) {
        // write your code here
        if(k == 0)
            return {};
        t = target;
        priority_queue<int, vector<int>, Compare> pq;
        find_closest(root, pq, k);
        vector<int> ans;
        while(!pq.empty())
        {
            ans.push_back(pq.top());
            pq.pop();
        }
        return ans;
    }
};
