#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include "binary_tree.h"

using namespace std;


int main()
{
    TreeNode *root = build_tree();
    TreeNode *last = NULL;
    stack<TreeNode *> s;
    vector<TreeNode *> ans;
    s.push(root);
    while(!s.empty())
    {
        TreeNode *p = s.top();
        if((!p->left && !p->right)
                || (last && (last == p->left || last == p->right)))
        {
            ans.push_back(p);
            s.pop();
            last = p;
        }
        else
        {
            if(p->right)
                s.push(p->right);
            if(p->left)
                s.push(p->left);
        }
    }
    return 0;
}
