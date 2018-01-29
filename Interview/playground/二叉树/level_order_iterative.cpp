#include <iostream>
#include <queue>
#include <string>
#include "binary_tree.h"

using namespace std;


int main()
{
    TreeNode *root = build_tree();
    queue<TreeNode *> q;
    q.push(root);
    while(!q.empty())
    {
        TreeNode *t = q.front();
        q.pop();
        cout<<t->val<<endl;
        if(t->left)
            q.push(t->left);
        if(t->right)
            q.push(t->right);
    }
    return 0;
}
