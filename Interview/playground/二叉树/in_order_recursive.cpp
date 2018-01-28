#include <iostream>
#include <vector>
#include <string>
#include "binary_tree.h"

using namespace std;


void in_order(TreeNode* root)
{
    if(!root)
        return;
    in_order(root->left);
    cout<<root->val<<endl;
    in_order(root->right);
}

int main()
{
    TreeNode *root = build_tree();
    in_order(root);
    return 0;
}
