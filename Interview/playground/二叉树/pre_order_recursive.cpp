#include <iostream>
#include <vector>
#include <string>
#include "binary_tree.h"

using namespace std;


void pre_order(TreeNode* root)
{
    if(!root)
        return;
    cout<<root->val<<endl;
    pre_order(root->left);
    pre_order(root->right);
}

int main()
{
    TreeNode *root = build_tree();
    pre_order(root);
    return 0;
}
