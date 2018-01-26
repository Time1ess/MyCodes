/*
struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
        
    }
};
*/
class Solution {
public:
    TreeLinkNode* GetFirst(TreeLinkNode* node)
    {
        if(!node)
            return NULL;
        if(node->left)
            return GetFirst(node->left);
        return node;
    }
    TreeLinkNode* GetFirstLeftParentParent(TreeLinkNode* node)
    {
        if(!node)
            return NULL;
        TreeLinkNode *parent = node->next;
        if(!parent)
            return NULL;
        TreeLinkNode *pparent = parent->next;
        if(!pparent)
            return NULL;
        while(pparent && pparent->left != parent)
        {
            parent = pparent;
            pparent = parent->next;
        }
        return pparent;
    }
    TreeLinkNode* GetNext(TreeLinkNode* pNode)
    {
        // if node has no parent, then find first node in node->right, otherwise NULL
        // if node in parent->left, then find first node in node->right, otherwise parent
        // if node in parent->right, then find first node in node->right, otherwise 
        // first left parent's ancestor
        // otherwise NULL
        if(!pNode)
            return NULL;
        TreeLinkNode* parent = pNode->next;
        TreeLinkNode* right_first = GetFirst(pNode->right);
        if(!parent)
            return right_first;
        if(parent->left == pNode)
            return right_first ? right_first : parent;
        else
            return right_first ? right_first : GetFirstLeftParentParent(pNode);
    }
};
