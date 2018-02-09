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
    while(!s.empty() || root)
    {
        if(root)
        {
            s.push(root);
            root = root->left;
        }
        else
        {
            root = s.top();
            s.pop();
            cout<<root->val<<endl;
            root = root->right;
        }
    }
    return 0;
}
