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
    s.push(root);
    while(!s.empty())
    {
        TreeNode *t = s.top();
        if(t->left && t->left != last)
        {
            do
            {
                t = t->left;
                s.push(t);
            } while(t->left);
            continue;
        }
        else
            s.pop();
        cout<<t->val<<endl;
        last = t;
        if(t->right)
            s.push(t->right);
    }
    return 0;
}
