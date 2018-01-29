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
    stack<TreeNode *> s;
    s.push(root);
    while(!s.empty())
    {
        TreeNode *t = s.top();
        s.pop();
        cout<<t->val<<endl;
        if(t->right)
            s.push(t->right);
        if(t->left)
            s.push(t->left);
    }
    return 0;
}
