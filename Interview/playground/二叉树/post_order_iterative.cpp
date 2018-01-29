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
        TreeNode *t = s.top();
        if(t->left && t->left != last && t->right != last)
        {
            do{
                t = t->left;
                s.push(t);
            } while(t->left);
            continue;
        }
        if(t->right && t->right != last)
        {
            s.push(t->right);
            continue;
        }
        s.pop();
        last = t;
        cout<<t->val<<endl;
    }
    return 0;
}
