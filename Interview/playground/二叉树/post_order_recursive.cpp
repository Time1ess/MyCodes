#include <iostream>
#include <vector>
#include <string>
#include "binary_tree.h"

using namespace std;


void post_order(TreeNode* root)
{
    if(!root)
        return;
    post_order(root->left);
    post_order(root->right);
    cout<<root->val<<endl;
}

int main()
{
    TreeNode *root = build_tree();
    post_order(root);
    return 0;
}
